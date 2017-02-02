

//Control de frecuecia con cursor

var synth = flock.synth({
    synthDef: {
        ugen: "flock.ugen.sawOsc",
        freq: {
            ugen: "flock.ugen.mouse.cursor",
            rate: "control",
            mul: 880,
            add: 110
        }
    }
});


var synth = flock.synth({
    synthDef: {
        ugen: "flock.ugen.sinOsc",
        freq: {
            ugen: "flock.ugen.mouse.cursor",
            rate: "control",
            mul: 900,
            add: 110
        }
    }
});


var synth = flock.synth({
    synthDef: {
        ugen: "flock.ugen.triOsc",
        freq: {
            ugen: "flock.ugen.mouse.cursor",
            rate: "control",
            mul: 920,
            add: 110
        }
    }
});


var synth = flock.synth({
    synthDef: {
        ugen: "flock.ugen.squareOsc",
        freq: {
            ugen: "flock.ugen.mouse.cursor",
            rate: "control",
            mul: 940,
            add: 110
        }
    }
});
