let addon = require('./build/Release/hello.node');

console.log(addon.hello());

console.log(addon.addNumber(1.0, 123.123));
console.log(addon.addNumber(1.0, "12311"));

let obj = addon.createObject();
obj.bbbb = 123;
console.log(obj);

let arr = addon.createArray();
arr.push("str");
console.log(arr);

addon.runCallback(
    () => {
        console.log("I AM callback");
    }
);

let cl = new addon.createClass();
console.log("class set 123, old::", cl.set('123'));
console.log("S", cl)
console.log("class set '456', old:", cl.set('456'));
console.log("class set '666', old:", cl.set('666'));
console.log("class set 777, old type:", typeof cl.set(777));
console.log("class set 888, old type:", typeof cl.set(888));
console.log("class get, value:", cl.get());
console.log("class get, type:", typeof cl.get());

delete cl;