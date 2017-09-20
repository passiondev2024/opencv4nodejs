const fs = require('fs');
const cv = require('../');

// a - z
const lccs = Array(26).fill(97).map((v, i) => v + i).map(ascii => String.fromCharCode(ascii));
exports.lccs = lccs;

const {
  CC_STAT_LEFT,
  CC_STAT_TOP,
  CC_STAT_WIDTH,
  CC_STAT_HEIGHT,
  CC_STAT_AREA
} = cv.cvTypes.connectedComponentsTypes;

const invert = img => img.threshold({
  thresh: 254,
  maxVal: 255,
  type: cv.cvTypes.thresholdTypes.THRESH_BINARY_INV
});

const getBoundingRect = component => new cv.Rect(
  component[CC_STAT_LEFT],
  component[CC_STAT_TOP],
  component[CC_STAT_WIDTH],
  component[CC_STAT_HEIGHT]
);

const getLetterBoundingRect = (img, isIorJ) => {
  const { stats } = invert(img).bgrToGray().connectedComponentsWithStats();
  const componentsOrderedBySize =
    stats.getDataAsArray().sort((s0, s1) => s1[CC_STAT_AREA] - s0[CC_STAT_AREA]);

  if (componentsOrderedBySize.length < 2) {
    return null;
  }

  // background actually is largest component so we take the next largest
  let largestComponent = componentsOrderedBySize[1];
  let letterRect = getBoundingRect(largestComponent);

  if (isIorJ && componentsOrderedBySize.length > 2) {
    let dotComponent = componentsOrderedBySize[2];

    if (largestComponent[CC_STAT_TOP] < dotComponent[CC_STAT_TOP]) {
      largestComponent = componentsOrderedBySize[2];
      dotComponent = componentsOrderedBySize[1];
      letterRect = getBoundingRect(largestComponent);
    }

    const dotRectXRight = dotComponent[CC_STAT_LEFT] + dotComponent[CC_STAT_WIDTH];
    const xLeft = Math.min(letterRect.x, dotComponent[CC_STAT_LEFT]);
    const letterRectYBottom = letterRect.y + letterRect.height;

    letterRect = new cv.Rect(
      xLeft,
      dotComponent[CC_STAT_TOP],
      Math.max(letterRect.width, dotRectXRight - xLeft),
      (letterRectYBottom - dotComponent[CC_STAT_TOP])
    );
  }

  return letterRect;
};

exports.centerLetterInImage = (img, isIorJ) => {
  const rect = getLetterBoundingRect(img, isIorJ);
  if (!rect) {
    return null;
  }

  const offX = (img.cols - rect.width) / 2;
  const offY = (img.rows - rect.height) / 2;
  const centeredRect = new cv.Rect(
    offX,
    offY,
    rect.width,
    rect.height
  );

  const centered = new cv.Mat(img.rows, img.cols, img.type, [255, 255, 255]);
  img.getRegion(rect).copyTo(centered.getRegion(centeredRect));

  return centered;
};

exports.saveConfusionMatrix = (
  testDataFiles,
  predict,
  numTestImagesPerClass,
  outputFile
) => {
  const confusionMat = new cv.Mat(26, 26, cv.cvTypes.CV_64F, 0);
  testDataFiles.forEach((files, label) => {
    files.forEach((file) => {
      const img = cv.imread(file);
      const predictedLabel = predict(img, label === 8 || label === 9);
      confusionMat.set(label, predictedLabel, confusionMat.at(label, predictedLabel) + 1);
    });
  });

  const confusionMatMatrix = [[''].concat(lccs)].concat(
    confusionMat.div(numTestImagesPerClass)
      .getDataAsArray().map((col, l) => [lccs[l]].concat(col.map(v => Math.round(v * 100) / 100)))
  );

  const csvRows = confusionMatMatrix.map(cols => cols.join(';'));
  fs.writeFileSync(outputFile, csvRows.join('\n'));
};
