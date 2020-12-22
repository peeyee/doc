/* error

error 在node里有特别的含义，如果没有处理error的事件，程序会终止并退出后续代码的执行。
*/
var events = require('events'); 
var emitter = new events.EventEmitter(); 
var catch_error = function catch_error() {console.log("hello error.");}
emitter.on('error',catch_error)

emitter.emit('error'); 
