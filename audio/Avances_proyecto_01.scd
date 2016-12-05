s.boot;

///// BINAURALES ASCENDENTES Y DESCENDENTES CON CONTROL DE PANEO Y FRECUENCIA

(
SynthDef(\binaural1_asc, {| senal, paneo, out, freq1 = 80, env, gate = 1, salida|
	senal = SinOsc.ar(Line.kr(30,80,150),0,0.1)/4;
	paneo = SinOsc.kr(0.1,0,2,0);
	env = EnvGen.ar(Env([0,1],[50]));
	salida = senal*env;
	salida = salida*EnvGen.ar(Env.cutoff(15), gate, doneAction:2);
	Out.ar(0, Pan4.ar(salida,paneo,1));
}).add;
)

a = Synth(\binaural1_asc)
a.set(\gate, 0)

(
SynthDef(\binaural1_desc, {| senal, paneo, out, freq1 = 80, env, gate = 1, salida|
	senal = SinOsc.ar(Line.kr(80,30,70),0,0.1)/4;
	paneo = SinOsc.kr(0.1,0,2,0);
	env = EnvGen.ar(Env([0,1],[5]));
	salida = senal*env;
	salida = salida*EnvGen.ar(Env.cutoff(15), gate, doneAction:2);
	Out.ar(0, Pan4.ar(salida,paneo,1));
}).add;
)

c = Synth(\binaural1_desc)
c.set(\gate, 0)

(
SynthDef(\binaural2_asc, {| senal, paneo, out, freq1 = 84, env, gate = 1, salida|
	senal = SinOsc.ar(Line.kr(30.5,80.5,150),0,0.1)/4;
	paneo = SinOsc.kr(0.1,0,2,0);
	env = EnvGen.ar(Env([0,1],[50]));
	salida = senal*env;
	salida = salida*EnvGen.ar(Env.cutoff(15), gate, doneAction:2);
	Out.ar(0, Pan4.ar(salida,paneo,1));
}).add;
)

b = Synth(\binaural2_asc)
b.set(\gate, 0)


(
SynthDef(\binaural2_desc, {| senal, paneo, out, freq1 = 84, env, gate = 1, salida|
	senal = SinOsc.ar(Line.kr(80.5,30.5,70),0,0.1)/4;
	paneo = SinOsc.kr(0.1,0,2,0);
	env = EnvGen.ar(Env([0,1],[5]));
	salida = senal*env;
	salida = salida*EnvGen.ar(Env.cutoff(15), gate, doneAction:2);
	Out.ar(0, Pan4.ar(salida,paneo,1));
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
        Synth(\perc_melody2, [\freq, b.next.midicps])!2;
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
Tdef(\ritmos_clicks,
	{
		Synth(\ritmos1);
		Synth(\ritmos2);
	};
);
)

Tdef(\ritmos_clicks).play


(
SynthDef(\ritmos1, {| senal, paneo, out, freq1 = 84, env, gate = 1, salida|
	senal = LFNoise0.ar(1);
	paneo = SinOsc.kr(0.5,0,2,0);
	env = EnvGen.ar(Env([0,1],[5]));
	salida = senal*env;
	salida = salida*EnvGen.ar(Env.cutoff(15), gate, doneAction:2);
	Out.ar(0, Pan2.ar(salida,paneo,1));
}).add;
)

Synth(\ritmos1)


(
SynthDef(\ritmos2, {| senal, paneo, out, freq1 = 84, env, gate = 1, salida|
	senal = LFNoise0.ar(3);
	paneo = SinOsc.kr(0.5,0,2,0);
	env = EnvGen.ar(Env([0,1],[5]));
	salida = senal*env;
	salida = salida*EnvGen.ar(Env.cutoff(15), gate, doneAction:2);
	Out.ar(0, Pan2.ar(salida,paneo,1));
}).add;
)

Synth(\ritmos2)



(
SynthDef(\sinpul, { | out = 0, frec = 6000, amp = 0.8, xpos = -1, ypos = -1 |
	var sig, env, pan, efecto, senal, paneo;
	senal = SinOsc.ar([frec, frec+10], 0, amp)*Pulse.ar([2+frec/2,frec/2],0.5,1);
	efecto = FreeVerb.ar(senal, 1, 5, 2, 1, 0.5);
	env = EnvGen.ar(Env.perc(0.05,2,1), doneAction:2);
	sig = senal*efecto;
	pan = Pan4.ar(sig*env, xpos, ypos, 1);
	Out.ar(0, Pan4.ar(sig*env, xpos, ypos, 1));
}).add;
)

u=Synth(\sinpul);


(
SynthDef(\sinpul1, {| senal, paneo, out, frec = 6000, env, gate = 1, salida|
	senal = SinOsc.ar([frec, frec+10], 1, 1)*Pulse.ar([2+frec/2,frec/2],0.5,1);
	env = EnvGen.ar(Env.perc(0.05,2,1), doneAction:2);
	salida = senal*env;
	salida = salida*EnvGen.ar(Env.cutoff(15), gate, doneAction:2);
	Out.ar(0, Pan2.ar(salida, -1, 1));
}).add;
)

u=Synth(\sinpul1);


---------------------------------

{SinOsc.ar(freq: LFNoise0.kr(800).range(600, 13000), mul: 0.1)!2}.play;

// Breaking it down:
{LFNoise0.kr(1).poll}.play; // watch a simple LFNoise0 in action
{LFNoise0.kr(1).range(500, 1500).poll}.play; // now with .range
{LFNoise0.kr(10).range(500, 1500).poll}.play; // now faster

(
SynthDef(\noise1, {| senal, paneo, out, freq1 = 84, env, gate = 1, salida|
	senal = SinOsc.ar(freq: LFNoise0.kr(800).range(600, 13000), mul: 0.1);
	paneo = SinOsc.kr(0.5,0,2,0);
	env = EnvGen.ar(Env([0,1],[5]));
	salida = senal*env;
	salida = salida*EnvGen.ar(Env.cutoff(15), gate, doneAction:2);
	Out.ar(0, Pan2.ar(salida,paneo,1));
}).add;
)

Synth(\noise1)

(
SynthDef(\noise2, {| senal, paneo, out, freq1 = 84, env, gate = 1, salida|
	senal = SinOsc.ar(freq: LFNoise0.kr(80).range(60, 1300), mul: 0.1);
	paneo = SinOsc.kr(0.1,0,2,0);
	env = EnvGen.ar(Env([0,1],[5]));
	salida = senal*env;
	salida = salida*EnvGen.ar(Env.cutoff(15), gate, doneAction:2);
	Out.ar(0, Pan4.ar(salida,paneo,1));
}).add;
)

Synth(\noise2)

(
Tdef(\noisesPan4,
	{
		Synth(\noise1);
		Synth(\noise2);
	};
);
)

Tdef(\noisesPan4).play

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
SynthDef(\chanexp_desc1, {| senal, paneo, out, freq1 = 300, freq2 = 600, env, gate = 1, salida|
	senal = SinOsc.ar(freq: [freq1, freq2], mul: Line.kr(0.5, 0, 27));
	env = EnvGen.ar(Env([0,1],[5]));
	salida = senal*env;
	salida = salida*EnvGen.ar(Env.cutoff(10), gate, doneAction:2);
	Out.ar(0,senal);
}).add;
)


~chanexp_desc1 = Synth(\chanexp_desc1)
~chanexp_desc1.set(\freq1, 80)
~chanexp_desc1.set(\freq1, 500)


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





 // Run this first ('turn reverb on' −− you won't hear anything at first)
r = {Out.ar(0, FreeVerb.ar(In.ar(55, 2), mix: 0.5, room: 0.9, mul: 0.4))}.play;

// Now run this second ('feed the busy tone into the reverb bus')
a = {Out.ar(55, SinOsc.ar([800, 880], mul: LFPulse.ar(2)))}.play;

a.free;


// Create the bus
~myBus = Bus.audio(s, 2);

// Turn on the reverb: read from myBus (source sound)
r = {Out.ar(0, FreeVerb.ar(In.ar(~myBus, 2), mix: 0.5, room: 0.9, mul: 0.4))}.play;

// Feed the busy tone into ~myBus
b = {Out.ar(~myBus, SinOsc.ar([800, 550], mul: LFPulse.ar(0.5)))}.play;

// Free both synths
r.free;
b.free;

(
Tdef(\reverb_pulse,
	{
		~myBus = Bus.audio(s, 2);
		~myBus1 = Bus.audio(s, 2);
		0.5.wait;
		r = {Out.ar(0, FreeVerb.ar(In.ar(~myBus, 2), mix: 1, room: 2, mul: 0.4))}.play;
		0.5.wait;
		b = {Out.ar(~myBus, SinOsc.ar([800, 550], mul: LFPulse.ar(0.5)))}.play;
		0.5.wait;
		t = {Out.ar(0, FreeVerb.ar(In.ar(~myBus1, 2), mix: 1, room: 2, mul: 0.4))}.play;
		1.wait;
		c = {Out.ar(~myBus1, SinOsc.ar([300, 650], mul: LFPulse.ar(0.7)))}.play;
	};
);
)


Tdef(\reverb_pulse).play


(
z = {
    var sig, freq;
    freq = MouseX.kr(20,14000,\exponential);
    sig = BMoog.ar(
        LFSaw.ar([freq * 0.99, freq * 1.01], 0, 0.1) ! 4,
        SinOsc.kr(SinOsc.kr(2),1.5pi,1550,1800),
        MouseY.kr(1,0,\linear),
        2);    // filter mode - bandpass
     (CombN.ar(sig, 0.4, [0.4,0.35],2) * 0.4) + (sig * 0.5);
}.play)
z.release


////// PRUEBAS CON MUSE //////////////



(
SynthDef(\prueba, {| senal, freq = 20 paneo, out, env, gate = 1, salida, oscilador = 0.5|
	senal = BMoog.ar(LFSaw.ar([freq * 0.99, freq * 1.01], 0.5, 0.1), SinOsc.kr(SinOsc.kr(oscilador),1.5pi,1550,1800), 0.2, 2);
	env = EnvGen.ar(Env([0,1],[5]));
	paneo = SinOsc.kr(0.1,0,2,0);
	salida = senal*env;
	salida = salida*EnvGen.ar(Env.cutoff(10), gate, doneAction:2);
	Out.ar(0, Pan4.ar(salida,paneo,1));
}).add;
)


~moog = Synth(\prueba)
~moog.set(\gate, 0)
~moog.set(\freq, 150)
~moog.set(\oscilador, 0.5)


(
j=OSCdef(\museOsca, {|msg|
	var delta1, delta2;
	msg.postln;
	delta1 = msg[1].linlin(0.1,0.9,20,60);
	delta2 = msg[1].linlin(0.1,0.9,0.05,5);
	~moog.set(\freq, delta1);
	~moog.set(\oscilador, delta2);
},'/muse/elements/alpha_relative')
)

------------------------
(
SynthDef(\pan4_LFN, {| senal, paneo, out, freq1 = 600, freq2 = 13000 env, gate = 1, salida|
	senal = SinOsc.ar(freq: LFNoise0.kr(800).range(freq1, freq2), mul: 0.1);
	paneo = SinOsc.kr(0.1,0,2,0);
	env = EnvGen.ar(Env([0,1],[5]));
	salida = senal*env;
	salida = salida*EnvGen.ar(Env.cutoff(5), gate, doneAction:2);
	Out.ar(0, Pan4.ar(salida,paneo,1));
}).add;
)

~pan4_LFN = Synth(\pan4_LFN)
~pan4_LFN.set(\gate, 0)

~pan4_LFN.set(\freq1, 60)
~pan4_LFN.set(\freq2, 100)

(
e=OSCdef(\museOsca, {|msg|
	var delta1, delta2;
	msg.postln;
	delta1 = msg[1].linlin(0.1,0.9,60,600);
	delta2 = msg[1].linlin(0.1,0.9,100,13000);
	~pan4_LFN.set(\freq1, delta1);
	~pan4_LFN.set(\freq2, delta2);
},'/muse/elements/alpha_relative')
)


(
x=OSCdef(\museOscx, {|msg|
	msg[1].postln;
	if(msg[1]==1,
		{"blink".post;
			~pan4_LFN.set(\freq1, [60, 13000, 600, 10000, 1000 ].choose);
			~pan4_LFN.set(\freq2, [60, 13000, 600, 10000, 1000 ].choose);
		}
	);
	},
	'/muse/elements/blink'
);
)


--------------------------------


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







--------------------------------


// PRUEBAS CON VARIOS SINTES Y MUSE

(
SynthDef(\sinpul1, {| senal, paneo, out, frec = 6000, env, gate = 1, salida|
	senal = SinOsc.ar([frec, frec+10], 1, 1)*Pulse.ar([2+frec/2,frec/2],0.5,1);
	env = EnvGen.ar(Env.perc(0.05,2,1), doneAction:2);
	salida = senal*env;
	salida = salida*EnvGen.ar(Env.cutoff(15), gate, doneAction:2);
	Out.ar(0, Pan2.ar(salida, -1, 1));
}).add;
)

~sinpul = Synth(\sinpul1)

(
Tdef(\prueba1_Muse,
	{
		1.wait;
		u=Synth(\sinpul1);
		1.wait;
		x=OSCdef(\museOscx, {|msg|
			var freq1 = 20, freq2 = 40, freq3 = 60, freq4 = 80;
			msg[1].postln;
			if(msg[1]==1,
				{"blink".post;
					~chanexp_desc1.set(\freq1, [freq1, freq2, freq3, freq4].choose);
				}
			);
			},
			'/muse/elements/blink'
		);

	};
);
)




















//////////////////////////////////



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














