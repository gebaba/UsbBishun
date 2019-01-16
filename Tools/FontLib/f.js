let fs = require('fs');
let SerialPort = require('serialport');

SerialPort.list().then(portData => console.log(portData));

let serialPort = new SerialPort('COM3', { autoOpen: false, baudRate: 115200, dataBits: 8, stopBits: 1, parity: 'none' });

let flash = fs.readFileSync('flash.bin');

let write = i => {
    let data = flash.slice(i * 4096, (i + 1) * 4096);
    console.log(i + '>>>' + data.length);
    serialPort.write(data);
    if (data.length < 4096) {
        serialPort.write('.'.repeat(4096 - data.length));
    }
}

serialPort.on('data', function (i) {
    return function () {
        let n = parseInt(flash.length / 4096);
        console.log('>>>' + i + '/' + n);
        if (i <= n) {
            write(i);
            i++;
        }
    };
}(1));
serialPort.open();
serialPort.write(flash.slice(0, 4096));
