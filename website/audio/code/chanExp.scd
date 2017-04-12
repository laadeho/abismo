



(
SynthDef(\chanexp_desc1, {| senal, paneo, out, freq1 = 20, freq2 = 40, freq3 = 60, freq4 = 80, env, gate = 1, salida, efex|
	senal = SinOsc.ar(freq: [freq1, freq2, freq3, freq4], mul: Line.kr(0.7, 0, 50));
	env = EnvGen.ar(Env([0,1],[5]));
	//efex = FreeVerb.ar(senal, 10, 5, 2, 1, 0);
	salida = senal*env;
	salida = salida*efex;
	salida = salida*EnvGen.ar(Env.cutoff(10), gate, doneAction:2);
	Out.ar(0,senal);
}).add;
)

(
x=OSCdef(\museOscx, {|msg|
	var freq1 = 20, freq2 = 40, freq3 = 60, freq4 = 80;
	msg[1].postln;
	if(msg[1]==1,
		{"blink".post;
			~chanexp_desc1.set(\freq1, [freq1, freq2, freq3, freq4].choose);
			~chanexp_desc1.set(\freq2, [freq1, freq2, freq3, freq4].choose);
			~chanexp_desc1.set(\freq3, [freq1, freq2, freq3, freq4].choose);
			~chanexp_desc1.set(\freq4, [freq1, freq2, freq3, freq4].choose);
		}
	);
	},
	'/muse/elements/blink'
);
)


~chanexp_desc1 = Synth(\chanexp_desc1)
~chanexp_desc1.set(\freq1, 80)
~chanexp_desc1.set(\freq1, 500)


(
Tdef(\chanExp_Muse,
	{
		~chanexp_desc1 = Synth(\chanexp_desc1);
		1.wait;

		x=OSCdef(\museOscx, {|msg|
			var freq1 = 20, freq2 = 40, freq3 = 60, freq4 = 80;
			msg[1].postln;
			if(msg[1]==1,
				{"blink".post;
					~chanexp_desc1.set(\freq1, [freq1, freq2, freq3, freq4].choose);
					~chanexp_desc1.set(\freq2, [freq1, freq2, freq3, freq4].choose);
					~chanexp_desc1.set(\freq3, [freq1, freq2, freq3, freq4].choose);
					~chanexp_desc1.set(\freq4, [freq1, freq2, freq3, freq4].choose);
				}
			);
			},
			'/muse/elements/blink'
		);

	};
);
)

Tdef(\chanExp_Muse).play
