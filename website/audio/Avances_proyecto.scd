

///// BINAURALES ASCENDENTES Y DESCENDENTES CON CONTROL DE PANEO Y FRECUENCIA

(
SynthDef(\binaural1_asc, {| senal, paneo, out, freq1 = 80, env, gate = 1, salida|
	senal = SinOsc.ar(Line.kr(30,80,150),0,0.1)/4;
	paneo = SinOsc.kr(0.1,0,1,0);
	env = EnvGen.ar(Env([0,1],[50]));
	salida = senal*env;
	salida = salida*EnvGen.ar(Env.cutoff(15), gate, doneAction:2);
	Out.ar(0, Pan2.ar(salida,paneo,1));
}).add;
)

a = Synth(\binaural1_asc)
a.set(\gate, 0)

(
SynthDef(\binaural1_desc, {| senal, paneo, out, freq1 = 80, env, gate = 1, salida|
	senal = SinOsc.ar(Line.kr(80,30,70),0,0.1)/4;
	paneo = SinOsc.kr(0.1,0,1,0);
	env = EnvGen.ar(Env([0,1],[5]));
	salida = senal*env;
	salida = salida*EnvGen.ar(Env.cutoff(15), gate, doneAction:2);
	Out.ar(0, Pan2.ar(salida,paneo,1));
}).add;
)

c = Synth(\binaural1_desc)
c.set(\gate, 0)

(
SynthDef(\binaural2_asc, {| senal, paneo, out, freq1 = 84, env, gate = 1, salida|
	senal = SinOsc.ar(Line.kr(30.5,80.5,150),0,0.1)/4;
	paneo = SinOsc.kr(0.1,0,1,0);
	env = EnvGen.ar(Env([0,1],[50]));
	salida = senal*env;
	salida = salida*EnvGen.ar(Env.cutoff(15), gate, doneAction:2);
	Out.ar(0, Pan2.ar(salida,paneo,1));
}).add;
)

b = Synth(\binaural2_asc)
b.set(\gate, 0)


(
SynthDef(\binaural2_desc, {| senal, paneo, out, freq1 = 84, env, gate = 1, salida|
	senal = SinOsc.ar(Line.kr(80.5,30.5,70),0,0.1)/4;
	paneo = SinOsc.kr(0.1,0,1,0);
	env = EnvGen.ar(Env([0,1],[5]));
	salida = senal*env;
	salida = salida*EnvGen.ar(Env.cutoff(15), gate, doneAction:2);
	Out.ar(0, Pan2.ar(salida,paneo,1));
}).add;
)

d = Synth(\binaural2_desc)
d.set(\gate, 0)


(
Tdef(\binaurales,
	{
		a = Synth(\binaural1_asc);
		b = Synth(\binaural2_asc);
		c = Synth(\binaural1_desc);
		d = Synth(\binaural2_desc);
	};
);
)

Tdef(\binaurales).play


///// DISEÑOS MELÓDICOS

(
p = Pbind(
\midinote, Pseq([57, 62, 64, 65, 67, 69], inf),
\dur, 1/2
);
)

p.play;

~pbinds1 = p.play;
~pbinds1.stop;
~pbinds1.resume;
~pbinds1.stop.reset;
~pbinds1.start;
~pbinds1.stop;


--------------------
// basado en ejemplo de Pseq

(
SynthDef(\perc_melody1,
    { arg out=0, freq=440, sustain=0.05;
        var env;
        env = EnvGen.kr(Env.perc(0.01, sustain, 0.2), doneAction:2);
        Out.ar(out, SinOsc.ar(freq, 0, env))
    }).add;
)


(
a = Pseq(#[60, 68, 79, 80, 93].rand, inf).asStream;
Routine({
    loop({
        Synth(\perc_melody1, [\freq, a.next.midicps]);
        0.7.wait;
    })
}).play;
)


(
SynthDef(\perc_melody2,
    { arg out=0, freq=440, sustain=0.5;
        var env;
        env = EnvGen.kr(Env.perc(0.01, sustain, 0.2), doneAction:2);
        Out.ar(out, SinOsc.ar(freq, 0, env))
    }).add;
)


(
b = Pseq(#[93, 98, 100, 102, 108], inf).asStream;
Routine({
    loop({
        Synth(\perc_melody2, [\freq, b.next.midicps]);
        0.6.wait;
    })
}).play;
)



(
Tdef(\perc_melodies,
	{
		(
			a = Pseq(#[60, 68, 79, 80, 93].rand, inf).asStream;
			Routine({
				loop({
					Synth(\perc_melody1, [\freq, a.next.midicps]);
					0.7.wait;
				})
			}).play;
		);

		(
			b = Pseq(#[93, 98, 100, 102, 108], inf).asStream;
			Routine({
				loop({
					Synth(\perc_melody2, [\freq, b.next.midicps]);
					0.6.wait;
				})
			}).play;
		)


	};
);
)

Tdef(\perc_melodies).play


(
Pbind
( \freq, Pwhite(40, 5000),
	\dur, Prand([0.15, 0.25, 0.3], inf),
	\amp, 0.2,
	\legato, 0.7
).trace.play;
)


(
Pbind( \note, Pseq([[0, 3, 7], [2, 5, 8], [3, 7, 10], [5, 8, 12]], 3),
	\dur, 0.15
).play;
)

// Fun with strum

(
Pbind(
	\note, Pseq([[−7, 3, 7, 10], [0, 3, 5, 8]], 2),
	\dur, 1,
	\legato, 0.4,
	\strum, 0.1 // try 0, 0.1, 0.2, etc 14
).play;
)

//Tempo

(
Pbind(
	\degree, Pseq([0, 0.1, 1, 2, 3, 4, 5, 6, 7]),
	\dur, 1;
).play(TempoClock(120/60)); // 120 beats over 60 seconds: 120 BPM
)

//Playing 2 or more Pbinds together

( // open big block
Pbind(
	\freq, Pn(Pseries(110, 111, 10)),
	\dur, 1/2,
	\legato, Pwhite(0.1, 1)
).play;

Pbind(
	\freq, Pn(Pseries(220, 222, 10)),
	\dur, 1/4,
	 \legato, Pwhite(0.1, 1)
).play;

Pbind(
	\freq, Pn(Pseries(330, 333, 10)),
	\dur, 1/6,
	\legato, 0.1
).play;
) // close big block


//////////// FORK //

// Basic fork example. Watch Post window:
(
{ "one thing".postln;
	2.wait;
	"another thing".postln;
	1.5.wait;
	"one last thing".postln;
}.fork;
)

(
t = TempoClock(76/60);
{
	Pbind(
		\note, Pseq([[4, 11], [6, 9]], 32),
		\dur, 1/6,
		\amp, Pseq([0.05, 0.03], inf)
	).play(t);

	2.wait;

	Pbind(
		\note, Pseq([[−25, −13, −1], [−20, −8, 4], \rest], 3),
		\dur, Pseq([1, 1, Rest(1)], inf),
		\amp, 0.1,
		\legato, Pseq([0.4, 0.7, \rest], inf)
	).play(t);
	2.75.wait;

	Pbind(
		\note, Pseq([23, 21, 25, 23, 21, 20, 18, 16, 20, 21, 23, 21], inf),
		\dur, Pseq([0.25, 0.75, 0.25, 1.75, 0.125, 0.125, 0.80, 0.20, 0.125, 0.125, 1], 1),   \amp, 0.1,
		\legato, 0.5
	).play(t);
}.fork(t);
)


---------------------------------



-----------------------------------

///// functions


f = { 2 + 2 }; // define the function
f.value; // put the function to work

"hello" ! 10;


////// RITMOS Y CLICKS

(
Tdef(\ritmos1,
	{
		{LFNoise0.ar(1)!2.poll}.play;
		{LFNoise0.ar(3)!2.poll}.play;
		{LFNoise0.ar(5)!2.poll}.play;
		{LFNoise0.ar(10)!2.poll}.play;
	};
);
)

Tdef(\ritmos1).play


---------------------------------

{SinOsc.ar(freq: LFNoise0.kr(800).range(600, 13000), mul: 0.1)!2}.play;

// Breaking it down:
{LFNoise0.kr(1).poll}.play; // watch a simple LFNoise0 in action
{LFNoise0.kr(1).range(500, 1500).poll}.play; // now with .range
{LFNoise0.kr(10).range(500, 1500).poll}.play; // now faster

(
SynthDef(\noise1, {| senal, paneo, out, freq1 = 84, env, gate = 1, salida|
	senal = SinOsc.ar(freq: LFNoise0.kr(800).range(600, 13000), mul: 0.1);
	paneo = SinOsc.kr(0.1,0,1,0);
	env = EnvGen.ar(Env([0,1],[5]));
	salida = senal*env;
	salida = salida*EnvGen.ar(Env.cutoff(15), gate, doneAction:2);
	Out.ar(0, Pan2.ar(salida,paneo,1));
}).add;
)

Synth(\noise1)

----------------------------------

//////////// BUSES Y CANALES


 {Out.ar(1, SinOsc.ar(440, 0, 0.1))}.play; // right channel



// start the effect
f = {Out.ar(0, BPF.ar(in: In.ar(55), freq: MouseY.kr(1000, 5000), rq: 0.1))}.play;
// start the source
n = {Out.ar(55, WhiteNoise.ar(0.5))}.play;

 // Warning: use headphones to avoid feedback
{SoundIn.ar(0)}.play; // same as In.ar(8): takes sound from the first input bus

// Stereo version
{SoundIn.ar([0, 1])}.play; // first and second inputs

// Some reverb just for fun?
{FreeVerb.ar(SoundIn.ar([0, 1]), mix: 0.5, room: 0.9)}.play;




//Paneo estereo

SynthDef(\soundin1, {| senal, paneo, out, freq1 = 84, env, gate = 1, salida|
	senal = SoundIn.ar([0]);
	paneo = SinOsc.kr(0.1,0,1,0);
	env = EnvGen.ar(Env([0,1],[5]));
	salida = senal*env;
	salida = salida*EnvGen.ar(Env.cutoff(15), gate, doneAction:2);
	Out.ar(0, Pan2.ar(salida,paneo,1));
}).add;
)

Synth(\soundin1)


//Paneo de 4 canales

(
SynthDef(\soundin2, {| senal, paneo, out, freq1 = 84, env, gate = 1, salida|
	senal = SoundIn.ar([0]);
	paneo = SinOsc.kr(0.1,0,2,0);
	env = EnvGen.ar(Env([0,1],[5]));
	salida = senal*env;
	salida = salida*EnvGen.ar(Env.cutoff(15), gate, doneAction:2);
	Out.ar(0, Pan4.ar(salida,paneo,1));
}).add;
)

Synth(\soundin2)

(
SynthDef(\pan4_bin, {| senal, paneo, out, freq1 = 84, env, gate = 1, salida|
	senal = SinOsc.ar(Line.kr(30,80,150),0,0.1)/4;
	paneo = SinOsc.kr(0.1,0,2,0);
	env = EnvGen.ar(Env([0,1],[5]));
	salida = senal*env;
	salida = salida*EnvGen.ar(Env.cutoff(15), gate, doneAction:2);
	Out.ar(0, Pan4.ar(salida,paneo,1));
}).add;
)

Synth(\pan4_bin)


(
SynthDef(\pan4_LFN, {| senal, paneo, out, freq1 = 84, env, gate = 1, salida|
	senal = SinOsc.ar(freq: LFNoise0.kr(800).range(600, 13000), mul: 0.1);
	paneo = SinOsc.kr(0.1,0,2,0);
	env = EnvGen.ar(Env([0,1],[5]));
	salida = senal*env;
	salida = salida*EnvGen.ar(Env.cutoff(5), gate, doneAction:2);
	Out.ar(0, Pan4.ar(salida,paneo,1));
}).add;
)

~pan4_LFN = Synth(\pan4_LFN)
~pan4_LFN.set(\gate, 0)



----/// En este ejemplo de Multichannel Expansion, SC crea un bus distinto para cada frecuencia que esta en forma de Arrays. El Line.kr sube la amplitud de 0 a 1 en 10 segundos.

{Out.ar(0, Saw.ar(freq: [220, 310, 405], mul: Line.kr(0, 1, 10)))}.play;

{Out.ar(0, SinOsc.ar(freq: [220, 310, 405], mul: Line.kr(0, 1, 10)))}.play;

(
SynthDef(\chanexp_asc, {| senal, paneo, out, freq1 = 84, env, gate = 1, salida|
	senal = SinOsc.ar(freq: [220, 310], mul: Line.kr(0, 0.5, 20));
	env = EnvGen.ar(Env([0,1],[5]));
	salida = senal*env;
	salida = salida*EnvGen.ar(Env.cutoff(15), gate, doneAction:2);
	Out.ar(0,senal);
}).add;
)


~chanexp_asc = Synth(\chanexp_asc)

(
SynthDef(\chanexp_asc1, {| senal, paneo, out, freq1 = 84, env, gate = 1, salida|
	senal = SinOsc.ar(freq: [250, 350], mul: Line.kr(0, 0.5, 25));
	env = EnvGen.ar(Env([0,1],[5]));
	salida = senal*env;
	salida = salida*EnvGen.ar(Env.cutoff(15), gate, doneAction:2);
	Out.ar(0,senal);
}).add;
)


~chanexp_asc1 = Synth(\chanexp_asc1)

(
SynthDef(\chanexp_desc, {| senal, paneo, out, freq1 = 84, env, gate = 1, salida|
	senal = SinOsc.ar(freq: [270, 400], mul: Line.kr(0.5, 0, 27));
	env = EnvGen.ar(Env([0,1],[5]));
	salida = senal*env;
	salida = salida*EnvGen.ar(Env.cutoff(10), gate, doneAction:2);
	Out.ar(0,senal);
}).add;
)


~chanexp_desc = Synth(\chanexp_desc)

(
SynthDef(\chanexp_desc1, {| senal, paneo, out, freq1 = 84, env, gate = 1, salida|
	senal = SinOsc.ar(freq: [300, 450], mul: Line.kr(0.5, 0, 27));
	env = EnvGen.ar(Env([0,1],[5]));
	salida = senal*env;
	salida = salida*EnvGen.ar(Env.cutoff(10), gate, doneAction:2);
	Out.ar(0,senal);
}).add;
)


~chanexp_desc1 = Synth(\chanexp_desc1)


(
Tdef(\channel_exp_ascdesc,
	{
		~chanexp_asc = Synth(\chanexp_asc);
		~chanexp_asc1 = Synth(\chanexp_asc1);
		~chanexp_desc = Synth(\chanexp_desc);
		~chanexp_desc1 = Synth(\chanexp_desc1);
	};
);
)

Tdef(\channel_exp_ascdesc).play






--------------------------------


 // A bunch of numbers
a = [1, 2, 3, 4, 5, 6, 7];
// Rescale to 0−127, linear to linear
a.linlin(1, 7, 0, 127).round(1);
// Rescale to 0−127, linear to exponential
a.linexp(1, 7, 0.01, 127).round(1); // don't use zero for an exponential range


////Theremin

{SinOsc.ar(freq: MouseX.kr(300, 2500), mul: MouseY.kr(0, 1))}.play;

{ SinOsc.ar }.plot; // sine wave
{ Saw.ar }.plot; // sawtooth wave
{ Pulse.ar }.plot; // square wave

{LFNoise0.ar(10).poll}.play;


 // This:
{SinOsc.kr(1).range(100, 200).poll}.play;
// ...is the same as this:
{SinOsc.kr(1, mul: 50, add: 150),.poll}.play;
// This:
{LFPulse.kr(1).range(100, 200).poll}.play;
//...is the same as this:
{LFPulse.kr(1, mul: 50, add: 100).poll}.play;














