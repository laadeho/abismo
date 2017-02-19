// Oscilador de sierra con limite de banda 

var synth = flock.synth({
    synthDef: {
        ugen: "flock.ugen.saw",
        freq: 100,
        mul: 1,
        add: 1,
        leakRate: 0.02
    }
    
})
