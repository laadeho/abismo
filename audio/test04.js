var gateS = 1;
var freqS = 440;
// Triggers a note whenever the mouse is clicked.
var synth = flock.synth({
    synthDef: {
        ugen: "flock.ugen.sinOsc",
        freq: 440,
        mul: {
            ugen: "flock.ugen.asr",
            attack: 0.25,
            sustain: 0.25,
            release: 0.5,
            gate: 1
        }
    }
});

function switchGate(){
    //gateS = int(random(2));
    /*
    if(gateS==0){
        gateS = 1;
    } else {
        gateS = 0;
    }
    */
}

        /*
var synth = flock.synth({
    synthDef: {
        ugen: "flock.ugen.playBuffer",
        buffer: {
            id: "chord",
            url: "sampleGitLow/bandPass.mp3"
        },

        speed: {
            ugen: "flock.ugen.mouse.cursor",
            options: {
                axis: "y"
            },
            add: 0.5
        },

        loop: 1,

        start: 0,

        end: {
            ugen: "flock.ugen.mouse.cursor",
            options: {
                axis: "x"
            }
        }
    }
});

var synth2 = flock.synth({
   synthDef: {
       id: "carrier",
       ugen: "flock.ugen.sinOsc",
       freq: 440,
       phase: {
           id: "mod",
           ugen: "flock.ugen.sinOsc",
           freq: 34.0,
           mul: {
               ugen: "flock.ugen.sinOsc",
               freq: 1/20,
               mul: flock.PI
           },
           add: flock.PI
       },
       mul: 0.25
   }
});
*/