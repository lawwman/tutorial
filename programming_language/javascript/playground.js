class Car {
    constructor() {
        this.name = 'car';
    }
    doSomething() {
        return this.name;
    }
}

const car = new Car();
console.log(car.doSomething());