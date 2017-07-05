p=ProxySpace.push(s.boot)
~out.play;
~out = ~alpha;

(
var gsrVal = 0, emula = false;
~newVal;
~alpha;

~alpha = {LFNoise1.kr(100,1)}.play;
//~alpha.poll;
(
if(~alpha.asFloat>=0.2,
	{"MAYOR"}
)
);
/*
if(emula,{
	"TRUE"
	// Todos tus valores aleatorios
},
{
	"FALSE"
});*/
OSCdef(\osc, {|msg|
	//msg.postln;
	gsrVal = (msg[1].asInteger.linlin(0,255,0,5)).asInteger;
	gsrVal.postcln;
	~newVal = gsrVal;
	~newVal.asInteger.postln;
	switch(gsrVal,
	0,
		{
			~sin = {SinOsc.ar(200,0,0.1)};
			postln("CERO")
		},
	1,
		{
			~sin = {SinOsc.ar(300,0,0.1)};
			postln("UNO")
		},
	2,
		{
			~sin = {SinOsc.ar(400,0,0.1)};
			postln("DOS")
		},
	3,
		{
			~sin = {SinOsc.ar(500,0,0.1)};
			postln("TRES")
		},
	4,
		{
			~sin = {SinOsc.ar(600,0,0.1)};
			postln("CUATRO")
		}
	)
}, '/gsr'
);

)