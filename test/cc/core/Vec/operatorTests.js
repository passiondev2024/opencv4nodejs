import { Vec } from 'dut';
import { assertError, assertPropsWithValue } from 'utils';
import { expect } from 'chai';

const OperatorRequiresArg = vec => (func, isScalar) => {
  it('should throw if no args', () => {
    assertError(
      () => vec[func].bind(vec)(),
      `expected arg to be ${isScalar ? 'a Scalar' : 'an instance of Vec'}`
    );
  });
};

module.exports = () => {
  describe('operators', () => {
    describe('Vec2', () => {
      const vec0 = new Vec(100, 200);
      const vec1 = new Vec(25, 50);
      const vec2 = new Vec(5, 4);
      const operatorRequiresArg = OperatorRequiresArg(vec0);
      describe('add', () => {
        operatorRequiresArg('add');

        it('add vectors', async () => {
          assertPropsWithValue(vec0.add(vec1))({ x: 125, y: 250 });
        });
      });

      describe('sub', () => {
        operatorRequiresArg('sub');

        it('subtract vectors', async () => {
          assertPropsWithValue(vec0.sub(vec1))({ x: 75, y: 150 });
        });
      });

      describe('mul', () => {
        operatorRequiresArg('mul', true);

        it('multiply vector by scalar', async () => {
          assertPropsWithValue(vec0.mul(2))({ x: 200, y: 400 });
        });
      });

      describe('div', () => {
        operatorRequiresArg('div', true);

        it('divide vector by scalar', async () => {
          assertPropsWithValue(vec0.div(2))({ x: 50, y: 100 });
        });
      });

      describe('hMul', () => {
        operatorRequiresArg('hMul');

        it('elementwise multiply vectors', async () => {
          assertPropsWithValue(vec0.hMul(vec2))({ x: 500, y: 800 });
        });
      });

      describe('hDiv', () => {
        operatorRequiresArg('hDiv');

        it('elementwise divide vectors', async () => {
          assertPropsWithValue(vec0.hDiv(vec2))({ x: 20, y: 50 });
        });
      });

      describe('dot', () => {
        operatorRequiresArg('dot');

        it('compute dot product of vectors', async () => {
          expect(vec0.dot(vec2)).to.equal(1300);
        });
      });
    });

    describe('Vec3', () => {
      const vec0 = new Vec(100, 200, 300);
      const vec1 = new Vec(25, 50, 75);
      const vec2 = new Vec(5, 4, 3);
      const operatorRequiresArg = OperatorRequiresArg(vec0);
      describe('add', () => {
        operatorRequiresArg('add');

        it('add vectors', async () => {
          assertPropsWithValue(vec0.add(vec1))({ x: 125, y: 250, z: 375 });
        });
      });

      describe('sub', () => {
        operatorRequiresArg('sub');

        it('subtract vectors', async () => {
          assertPropsWithValue(vec0.sub(vec1))({ x: 75, y: 150, z: 225 });
        });
      });

      describe('mul', () => {
        operatorRequiresArg('mul', true);

        it('multiply vector by scalar', async () => {
          assertPropsWithValue(vec0.mul(2))({ x: 200, y: 400, z: 600 });
        });
      });

      describe('div', () => {
        operatorRequiresArg('div', true);

        it('divide vector by scalar', async () => {
          assertPropsWithValue(vec0.div(2))({ x: 50, y: 100, z: 150 });
        });
      });

      describe('hMul', () => {
        operatorRequiresArg('hMul');

        it('elementwise multiply vectors', async () => {
          assertPropsWithValue(vec0.hMul(vec2))({ x: 500, y: 800, z: 900 });
        });
      });

      describe('hDiv', () => {
        operatorRequiresArg('hDiv');

        it('elementwise divide vectors', async () => {
          assertPropsWithValue(vec0.hDiv(vec2))({ x: 20, y: 50, z: 100 });
        });
      });

      describe('dot', () => {
        operatorRequiresArg('dot');

        it('compute dot product of vectors', async () => {
          expect(vec0.dot(vec2)).to.equal(2200);
        });
      });

      describe('cross', () => {
        operatorRequiresArg('cross');

        it('compute cross product of vectors', async () => {
          assertPropsWithValue(new Vec(1, 0, 0).cross(new Vec(0, 1, 0)))({ x: 0, y: 0, z: 1 });
        });
      });
    });

    describe('Vec4', () => {
      const vec0 = new Vec(50, 100, 200, 300);
      const vec1 = new Vec(10, 25, 50, 75);
      const vec2 = new Vec(2, 5, 4, 3);
      const operatorRequiresArg = OperatorRequiresArg(vec0);
      describe('add', () => {
        operatorRequiresArg('add');

        it('add vectors', async () => {
          assertPropsWithValue(vec0.add(vec1))({ w: 60, x: 125, y: 250, z: 375 });
        });
      });

      describe('sub', () => {
        operatorRequiresArg('sub');

        it('subtract vectors', async () => {
          assertPropsWithValue(vec0.sub(vec1))({ w: 40, x: 75, y: 150, z: 225 });
        });
      });

      describe('mul', () => {
        operatorRequiresArg('mul', true);

        it('multiply vector by scalar', async () => {
          assertPropsWithValue(vec0.mul(2))({ w: 100, x: 200, y: 400, z: 600 });
        });
      });

      describe('div', () => {
        operatorRequiresArg('div', true);

        it('divide vector by scalar', async () => {
          assertPropsWithValue(vec0.div(2))({ w: 25, x: 50, y: 100, z: 150 });
        });
      });

      describe('hMul', () => {
        operatorRequiresArg('hMul');

        it('elementwise multiply vectors', async () => {
          assertPropsWithValue(vec0.hMul(vec2))({ w: 100, x: 500, y: 800, z: 900 });
        });
      });

      describe('hDiv', () => {
        operatorRequiresArg('hDiv');

        it('elementwise divide vectors', async () => {
          assertPropsWithValue(vec0.hDiv(vec2))({ w: 25, x: 20, y: 50, z: 100 });
        });
      });

      describe('dot', () => {
        operatorRequiresArg('dot');

        it('compute dot product of vectors', async () => {
          expect(vec0.dot(vec2)).to.equal(2300);
        });
      });
    });
  });
};
