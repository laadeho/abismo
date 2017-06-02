s.boot;
s.meter;
Server.default.makeGui;
s.recChannels_(4); // or whatever number of channels
s.record;
stop.record;

c = 4;
s.options.numOutputBusChannels = c;
s.options.sampleRate = 48000;
s.boot;
s.recChannels = c;
s.recHeaderFormat = "WAV";



/////////////////// EUFORIA00

(
SynthDef(\high, {|senal, paneo, out, env, gate = 1, density = 10, salida, pan1 = 0.1, amp = 0.1, bus = 0, f1 = 1000, f2 = 2000|
	senal = SinOsc.ar(f1 + f2);
	paneo = SinOsc.kr(pan1,0,2,0);
	env = EnvGen.ar(Env.adsr(25, 2000, amp, 10, -4), gate, doneAction:2);
	salida = senal*env;
	Out.ar(bus, Pan4.ar(salida, paneo, level:amp));
}).add;
);

~high = Synth(\high)
~high.set(\gate, 0)


(
SynthDef(\Brown, {|senal, paneo, out, env, gate = 1, density = 10, salida, pan1 = 0.1, amp = 0.5, bus = 0|
	senal = BrownNoise.ar(0.4);
	paneo = SinOsc.kr(pan1,0,2,0);
	env = EnvGen.ar(Env.adsr(2, 20, amp, 10, -4), gate, doneAction:2);
	salida = senal*env;
	Out.ar(bus, Pan4.ar(salida, paneo, level:amp));
}).add;
);

~brown = Synth(\Brown)
~brown.set(\gate, 0)
~brown.free;


(
SynthDef(\Gray, {|senal, paneo, out, env, gate = 1, density = 10, salida, pan1 = 0.05, amp = 0.4, bus = 0|
	senal = GrayNoise.ar(0.2);
	paneo = SinOsc.kr(pan1,0,2,0);
	env = EnvGen.ar(Env.adsr(2, 20, amp, 10, -4), gate, doneAction:2);
	salida = senal*env;
	Out.ar(bus, Pan4.ar(salida, paneo, level:amp));
}).add;
);



~gray = Synth(\Gray)
~gray.set(\amp, 0)

(
SynthDef(\dustEnv00, {|senal, paneo, out, env, gate = 1, envgen, salida, pan1 = 0.1, amp = 1, density = 4, f1 = 90, f2 = 100|
	env = Env([0.0, [-0.2, 0.5], 0.0, 1.0, [-0.4, 0.9], 0.0], [0.05, 0.1, 0.01, 1.0, 1.5], -4);
	envgen = EnvGen.ar(env, Dust.ar(density));
	senal =  SinOsc.ar(envgen * f1 + f2) * envgen * 0.1;
	//paneo = SinOsc.kr(pan1,0,2,0);
	//env = EnvGen.ar(Env.adsr(60, 20, amp, 10, -4), gate, doneAction:2);
	salida = senal;
	Out.ar(out, Pan4.ar(salida, paneo));
}).add;
)

~dustEnv00 = Synth(\dustEnv00)
	~dustEnv00.set(\f1, 200);
~dustEnv00.set(\f2, 300);


(
SynthDef(\dustEnv01, {|senal, paneo, out, env, gate = 1, envgen, salida, pan1 = 0.1, amp = 1, density = 7, f1 = 1, f2 = 5|
	env = Env([0.0, [-0.2, 0.5], 0.0, 1.0, [-0.4, 0.9], 0.0], [0.05, 0.1, 0.01, 1.0, 1.5], -4);
	envgen = EnvGen.ar(env, Dust.ar(density));
	senal =  LFSaw.ar(envgen * f1 + f2) * envgen * 0.1;
	//paneo = SinOsc.kr(pan1,0,2,0);
	//env = EnvGen.ar(Env.adsr(60, 20, amp, 10, -4), gate, doneAction:2);
	salida = senal;
	Out.ar(out, Pan4.ar(salida, paneo));
}).add;
)

~dustEnv01 = Synth(\dustEnv01)
~dustEnv01.set(\f1, 40);
~dustEnv01.set(\f2, 200);


s.scope;

(
y=OSCdef(\museOscy, {|msg|
	var freq;
	msg[1].postln;
	if(msg[1]==1,
		{"blink".post;
			~dustEnv01.set(\out, [0, 1, 2, 3].choose);
			~dustEnv00.set(\out, [0, 1, 2, 3].choose);

		}
	)
},
'/muse/elements/blink'
);
)

(
c=OSCdef(\museOscc, {|msg|
	var alpha1, alpha2;
	msg.postln;
	alpha1 = msg[1].linlin(0.1,0.9, 1, 40);
	alpha2 = msg[1].linlin(0.1,0.9, 5, 60);
	~dustEnv01.set(\f1, alpha1);
	~dustEnv01.set(\f2, alpha2);
},'/muse/elements/alpha_relative')
);

(
d=OSCdef(\museOscd, {|msg|
	var alpha1, alpha2;
	msg.postln;
	alpha1 = msg[1].linlin(0.1,0.9, 90, 200);
	alpha2 = msg[1].linlin(0.1,0.9, 100, 300);
	~dustEnv00.set(\f1, alpha1);
	~dustEnv00.set(\f2, alpha2);
},'/muse/elements/gamma_relative')
);


(
y=OSCdef(\museOscy, {|msg|
	var freq;
	msg[1].postln;
	if(msg[1]==1,
		{"blink".post;
			~gray.set(\amp, [0, 0.4].choose);
			~brown.set(\amp, [0, 0.5].choose);
			~high.set(\amp, [0, 0.1].choose);
			~high.set(\f1, [1000, 2000, 3000, 5000, 800].choose);
			~high.set(\f2, [900, 1500, 3500, 4000, 6000].choose);

		}
	)
},
'/muse/elements/blink'
);
)

y.free;





(
Tdef(\Euforia00, {
	1.wait;
	~high = Synth(\high);
	0.1.wait;
	(
		x=OSCdef(\museOscx, {|msg|
			var freq;
			msg[1].postln;
			if(msg[1]==1,
				{"blink".post;
					~gray.set(\amp, [0, 0.4].choose);
					~brown.set(\amp, [0, 0.5].choose);
					~high.set(\amp, [0, 0.1].choose);
					~high.set(\f1, [1000, 2000, 3000, 5000, 800].choose);
					~high.set(\f2, [900, 1500, 3500, 4000, 6000].choose);

				}
			)
		},
		'/muse/elements/blink'
		);
	);
	0.2.wait;
	~brown = Synth(\Brown);
	0.2.wait;
	~gray = Synth(\Gray);
	0.2.wait;
	~dustEnv00 = Synth(\dustEnv00);
	0.2.wait;
	~dustEnv01 = Synth(\dustEnv01);
	1.wait;
	(
		y=OSCdef(\museOscy, {|msg|
			var freq;
			msg[1].postln;
			if(msg[1]==1,
				{"blink".post;
					~dustEnv01.set(\out, [0, 1, 2, 3].choose);
					~dustEnv00.set(\out, [0, 1, 2, 3].choose);

				}
			)
		},
		'/muse/elements/blink'
		);
	);
	1.wait;
	(
		e=OSCdef(\museOsce, {|msg|
			var freq;
			msg[1].postln;
			if(msg[1]==1,
				{"blink".post;
					~dustEnv01.set(\out, [0, 1, 2, 3].choose);
					~dustEnv00.set(\out, [0, 1, 2, 3].choose);

				}
			)
		},
		'/muse/elements/blink'
		);
	);
	1.wait;
	(
		d=OSCdef(\museOscd, {|msg|
			var alpha1, alpha2;
			msg.postln;
			alpha1 = msg[1].linlin(0.1,0.9, 90, 200);
			alpha2 = msg[1].linlin(0.1,0.9, 100, 300);
			~dustEnv00.set(\f1, alpha1);
			~dustEnv00.set(\f2, alpha2);
		},'/muse/elements/gamma_relative')
	);
	100.wait;
	~brown.free;
	~gray.free;/////////////////////// corrige !!!
	~dustEnv00.free;
	~dustEnv01.free;
	10.wait;
	~high.free;
	x.free;
	y.free;
	d.free;
	e.free;
	"F I N".postln;
});
);

Tdef(\Euforia00).play;