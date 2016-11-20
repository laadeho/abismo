var synth = flock.synth({
    synthDef: {
        ugen: "flock.ugen.playBuffer",
        buffer: {
            id: "chord",
            url: "samples/ae.mp3"
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