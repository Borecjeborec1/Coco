class mathLib {
    constructor() {
        this.some_const = 1231;
        this.some_const2 = 1231;
    }
    addConst(x) {
        return x + this.some_const;
    }
}

const idk = new mathLib();
console.log(idk.addConst(123));
