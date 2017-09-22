const cv = global.dut;
const { assertPropsWithValue, funcShouldRequireArgs, readTestImage } = global.utils;
const { assert } = require('chai');

describe('ximgproc', () => {
  if (!cv.xmodules.ximgproc) {
    it('compiled without  ximgproc');
    return;
  }

  let testImg;

  before(() => {
    testImg = readTestImage().resizeToMax(250);
  });

  describe('SuperpixelSEEDS', () => {
    const numSuperpixels = 100;
    const numLevels = 2;

    describe('constructor', () => {
      funcShouldRequireArgs(() => new cv.SuperpixelSEEDS());

      it('should be constructable with required args', () => {
        const superpixelSeeds = new cv.SuperpixelSEEDS(testImg, numSuperpixels, numLevels);
        assertPropsWithValue(superpixelSeeds)({
          image: testImg,
          numSuperpixels,
          numLevels
        });
      });
    });

    describe('iterate', () => {
      it('should iterate with default values', () => {
        const superpixelSeeds = new cv.SuperpixelSEEDS(testImg, numSuperpixels, numLevels);
        superpixelSeeds.iterate();
        assert(superpixelSeeds.numCalculatedSuperpixels > 0, 'no superpixels calculated');
        assertPropsWithValue(superpixelSeeds.labels)({
          rows: testImg.rows, cols: testImg.cols, type: cv.CV_32S
        });
      });
    });
  });
});
