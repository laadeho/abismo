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



//////// SOLEDAD01 ///////////////////

/////// MOVER LOS BUFFERS A LA CARPETA CORRESPONDIENTE

(
		SynthDef(\perc_Abajo, {|senal, paneo, out, env, gate = 1, salida|
			senal = SinOsc.ar(55);
			env = EnvGen.ar(Env.perc(0.01, 4, 0.5, -4), gate, doneAction:2);
			salida = senal*env;
			Out.ar(1, salida);
		}).add;
	);
	1.wait;
	~perc_Abajo = Synth(\perc_Abajo);
	"sinte perc_Abajo OK".postln;
	1.wait;
	~perc_Abajo.set(\gate, 0);
	1.wait;
	(
		SynthDef(\perc_D, {|senal, paneo, out, env, gate = 1, salida|
			senal = SinOsc.ar(73.42);
			env = EnvGen.ar(Env.perc(0.01, 4, 0.5, -4), gate, doneAction:2);
			salida = senal*env;
			Out.ar(1, salida);
		}).add;
	);
	1.wait;
	~perc_D = Synth(\perc_D);
	"sinte perc_Abajo OK".postln;
	1.wait;
	~perc_E.set(\gate, 0);
	1.wait;
	(
		SynthDef(\perc_B, {|senal, paneo, out, env, gate = 1, salida|
			senal = SinOsc.ar(61.74);
			env = EnvGen.ar(Env.perc(0.01, 4, 0.5, -4), gate, doneAction:2);
			salida = senal*env;
			Out.ar(1, salida);
		}).add;
	);
	1.wait;
	~perc_B = Synth(\perc_B);
	"sinte perc_Abajo OK".postln;
	1.wait;
	~perc_B.set(\gate, 0);



	(
		SynthDef(\thankyou, {| out = 0, gate = 1, amp = 0.3, mixArg = 0.5, roomArg = 0.5, dir = 1, pos = 0|
			var senal, efecto, env;
			senal = PlayBuf.ar(~thankyou_buf.numChannels, ~thankyou_buf.bufnum, dir, 1, pos, 0, doneAction:0)*8;
			efecto = FreeVerb.ar(senal, mixArg, roomArg, 0.5);
			env = EnvGen.ar(Env.adsr(0.1, 0.3, 0.7, 2, 0.7, -10), gate, doneAction:2);
			senal = efecto*env;
			Out.ar(out, senal*amp);
		}).add
	);

	1.wait;

	~thankyou = Synth(\thankyou);
	~thankyou.set(\gate, 0);

(
		SynthDef(\hithere, {| out = 0, gate = 1, amp = 0.5, mixArg = 0.5, roomArg = 0.5, dir = 1, pos = 0|
			var senal, efecto, env;
			senal = PlayBuf.ar(~hithere_buf.numChannels, ~hithere_buf.bufnum, dir, 1, pos, 0, doneAction:0)*6;
			efecto = FreeVerb.ar(senal, mixArg, roomArg, 0.5);
			env = EnvGen.ar(Env.adsr(10, 2, 0.5, 20, 0.7, -10), gate, doneAction:2);
			senal = efecto*env;
			Out.ar(out, senal*amp);
		}).add
	);

	1.wait;

	~hithere = Synth(\hithere);
	~hithere.set(\gate, 0);


(
		SynthDef(\newthings, {| out = 0, gate = 1, amp = 0.5, mixArg = 0.5, roomArg = 0.5, dir = 1, pos = 0|
			var senal, efecto, env;
			senal = PlayBuf.ar(~newthings_buf.numChannels, ~newthings_buf.bufnum, dir, 1, pos, 0, doneAction:0)*5;
			efecto = FreeVerb.ar(senal, mixArg, roomArg, 0.5);
			env = EnvGen.ar(Env.adsr(10, 2, 0.5, 2, 0.7, -10), gate, doneAction:2);
			senal = efecto*env;
			Out.ar(out, senal*amp);
		}).add
	);

	1.wait;

	~newthings = Synth(\newthings);
	~newthings.set(\gate, 0);


/////// METER TODOS ESTOS SINTES EN TDEFS PARA QUE SALGAN Y NO SATUREN EL SERVIDOR!!!

(
Tdef(\newthings, {
	~newthings = Synth(\newthings);
	5.wait;
	~newthings.set(\gate, 0);
});
)

Tdef(\newthings).play


(
Tdef(\hithere, {
	~hithere = Synth(\hithere);
	2.wait;
	~hithere.set(\gate, 0);
});
)

Tdef(\hithere).play     /////// checa porque este no se apaga!!!


(
Tdef(\thankyou, {
	~thankyou = Synth(\thankyou);
	5.wait;
	~thankyou.set(\gate, 0);
});
)

Tdef(\thankyou).play     /////// checa porque este no se apaga!!!




(
		r=OSCdef(\museOscr, {|msg|
			var freq;
			msg[1].postln;
			if(msg[1]==1,
				{"blink".post;
					~choose = Synth([\perc_Abajo, \perc_D, \perc_B].choose);
				},{
					"NOT".postln;
				}
			)
		},
		'/muse/elements/blink'
		);
	);


(
		i=OSCdef(\museOsci, {|msg|
			var freq;
			msg[1].postln;
			if(msg[1]==1,
				{"blink".post;
					~choose = Tdef([\thankyou, \hithere, \newthings].choose).play;
				},{
					"NOT".postln;
				}
			)
		},
		'/muse/elements/blink'
		);
	)