import { Mat, matTypes } from 'dut';
import { assertError } from 'utils';
import { assertDataDeepEquals, assertMetaData } from './matTestUtils';

const operatorRequiresArg = (func, isScalar) => {
  it('should throw if no args', () => {
    assertError(
      () => {
        const mat = new Mat();
        return mat[func].bind(mat)();
      },
      `expected arg to be a ${isScalar ? 'Scalar' : 'Mat'}`
    );
  });
};

module.exports = () => {
  describe('add', () => {
    operatorRequiresArg('add');

    it('add matrices', async () => {
      const mat = new Mat([
        [10, 20],
        [10, 20]
      ], matTypes.CV_8U);
      const expectedResult = [
        [20, 40],
        [20, 40]
      ];
      const res = mat.add(mat);
      assertMetaData(res)(2, 2, matTypes.CV_8U);
      assertDataDeepEquals(res.getData(), expectedResult);
    });
  });

  describe('sub', () => {
    operatorRequiresArg('sub');

    it('subtract matrices', async () => {
      const mat0 = new Mat([
        [20, 40],
        [20, 40]
      ], matTypes.CV_8U);
      const mat1 = new Mat([
        [10, 20],
        [10, 20]
      ], matTypes.CV_8U);
      const expectedResult = mat1.getData();
      const res = mat0.sub(mat1);
      assertMetaData(res)(2, 2, matTypes.CV_8U);
      assertDataDeepEquals(res.getData(), expectedResult);
    });
  });

  describe('mul', () => {
    operatorRequiresArg('mul', true);

    it('multiply matrix by scalar', async () => {
      const mat = new Mat([
        [20, 40],
        [20, 40]
      ], matTypes.CV_8U);
      const scalar = 2;
      const expectedResult = [
        [40, 80],
        [40, 80]
      ];
      const res = mat.mul(scalar);
      assertMetaData(res)(2, 2, matTypes.CV_8U);
      assertDataDeepEquals(res.getData(), expectedResult);
    });
  });

  describe('div', () => {
    operatorRequiresArg('div', true);

    it('divide matrix by scalar', async () => {
      const mat = new Mat([
        [20, 40],
        [20, 40]
      ], matTypes.CV_8U);
      const scalar = 2;
      const expectedResult = [
        [10, 20],
        [10, 20]
      ];
      const res = mat.div(scalar);
      assertMetaData(res)(2, 2, matTypes.CV_8U);
      assertDataDeepEquals(res.getData(), expectedResult);
    });
  });

  describe('and', () => {
    operatorRequiresArg('and');

    it('apply and to matrices', async () => {
      const mat0 = new Mat([
        [15, 15],
        [15, 15]
      ], matTypes.CV_8U);
      const mat1 = new Mat([
        [15, 0],
        [12, 3]
      ], matTypes.CV_8U);
      const expectedResult = [
        [15, 0],
        [12, 3]
      ];
      const res = mat0.and(mat1);
      assertMetaData(res)(2, 2, matTypes.CV_8U);
      assertDataDeepEquals(res.getData(), expectedResult);
    });
  });

  describe('or', () => {
    operatorRequiresArg('or');

    it('apply or to matrices', async () => {
      const mat0 = new Mat([
        [15, 15],
        [0, 0]
      ], matTypes.CV_8U);
      const mat1 = new Mat([
        [15, 0],
        [12, 3]
      ], matTypes.CV_8U);
      const expectedResult = [
        [15, 15],
        [12, 3]
      ];
      const res = mat0.or(mat1);
      assertMetaData(res)(2, 2, matTypes.CV_8U);
      assertDataDeepEquals(res.getData(), expectedResult);
    });
  });
};
