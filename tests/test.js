const { expect } = require('chai');
const coco = require('../index');
const fs = require("fs")

const inputFolder = './tests/input-files/';
const outputFolder = './tests/output-files/';

const testFiles = fs.readdirSync(inputFolder).filter(file => file.endsWith('.js'));
testFiles.forEach((file) => {
  describe(`${file} file`, function () {
    this.timeout(50000);

    before(async () => {
      await coco.init(`${inputFolder}${file}`, `${outputFolder}${file.replace(".js", ".cc")}`);
    });

    it('should build successfully', async () => {
      const buildResult = await coco.build();
      expect(buildResult).to.be.true;
    });

    it('should compile successfully', async () => {
      const compileResult = await coco.compile();
      expect(compileResult).to.be.true;
    });

    // it('should run successfully', async () => {
    //   coco.run();
    // });
  });

})
