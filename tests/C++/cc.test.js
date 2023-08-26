const { expect } = require('chai');
const coco = require('../../index.js'); // Adjust the path accordingly
const path = require("path")

describe('generating variable types', function () {
  it('should convert let variables to C++ auto', async function () {
    const jsFile = path.join(__dirname, "./input/all-types.js")
    const ccFile = path.join(__dirname, "./input/all-types.cc")
    const binaryFile = path.join(__dirname, "./output/all-types.exe")
    await coco.init(jsFile, ccFile, binaryFile);
    await coco.build();
    await coco.compile();
    await coco.run();
    coco.expect().to.equal()

  });

});