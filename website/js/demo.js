// VARIABLES DE AUDIO
var gateS = 1;
var freqS = 440;

// VARIABLES DE GRAFICA
var filaDeg, alfaIntro;
var alfa, beta, gamma, delta, theta, conc, med, gsr, BPM;
var datos = [
	"alfa", "beta", "gamma", "delta", "theta", "conc", "med", "gsr", "BPM"
];
var numVal = 9;
var val = [];
var radio;
var pX, pY; 
var coordX = [], coordY = [];
var grafica = 0;
var numGraficas = 2;

function setup(){
	createCanvas(windowWidth, windowHeight);
	colorMode(HSB, 100,100,100);
	background(0);
	filaDeg = 100/height;
	pX = width/2;
	pY = height/2;
	radio = height/5;
}
function draw(){
	background(0);
	degradado();
	simulaDatos();
	textSize(12);
	fill(0,0,100);
	textAlign(CENTER);
	text("SIMULACION DE DATOS OBTENIDOS", width/2, height-50-radio/6);
	fill(0,0,80);
	text("oprimir flecha derecha o izquierda para cambiar visual", width/2, height-30-radio/6);
	textSize(11);

	chooseGraph();
}

function chooseGraph(){
	calculaNodos();
	switch(grafica){
		//////////////////////////////////////////////////////////// CASO 0
		case 0:
		push();
		stroke(100);
		fill(0,0,100,0.05);
		for(var j=0;j<20;j++){
			strokeWeight(1-j*0.1);
			beginShape();
			for(var i=0;i<numVal;i++){
				vertex(pX+coordX[i]*(j*0.05), pY+coordY[i]*(j*0.05));
			}
			endShape(CLOSE);
		}
		
		stroke(0,0,100);
		for(var j=0;j<20;j++){
			for(var i=0;i<numVal;i++){
				strokeWeight(j*.25);
				point(pX+coordX[i]*(j*0.05), pY+coordY[i]*(j*0.05));
			}
		}

		textAlign(LEFT);	
		fill(0,0,100);
		noStroke();
		for(var i=0;i<numVal;i++){
			text(datos[i]+": "+val[i], pX+12+coordX[i], pY+coordY[i]);
		}
		pop();
		break;
		//////////////////////////////////////////////////////////// CASO 1
		case 1:
		push();
		stroke(100);
		fill(0,0,100,0.05);
		for(var j=0;j<20;j++){
			strokeWeight(1-j*0.1);
			beginShape();
			vertex(0,height);
			for(var i=0;i<numVal;i++){
				vertex(coordX[i], coordY[i]+(j*25));
			}
			vertex(width,height);
			endShape(CLOSE);
		}

		stroke(0,0,100);
		for(var j=0;j<20;j++){
			for(var i=0;i<numVal;i++){
				strokeWeight(5-j*.25);
				point(coordX[i], coordY[i]+(j*25));
			}
		}
		pop();
		break;
	}

}

function calculaNodos(){
	/////////////////////////////////////////////////////////////////////////
	// CALCULA NODOS
	switch(grafica){
		case 0: // ARREGLO POLAR
		for(var i=0;i<numVal;i++){
			if(i<numVal-1){
				coordX[i] = cos(radians(360/numVal)*i)*(radio+val[i]*50);
				coordY[i] = sin(radians(360/numVal)*i)*(radio+val[i]*50);			
			} else {
				coordX[i] = cos(radians(360/numVal)*i)*(radio+val[i]*0.25);
				coordY[i] = sin(radians(360/numVal)*i)*(radio+val[i]*0.25);
			}
		}
		break;
		case 1: // ARREGLO CARTESIANO
		for(var i=0;i<numVal;i++){
				coordX[i] = width/(numVal-1)*i;
			if(i<numVal-1){
				coordY[i] = radio+val[i]*150;			
			} else {
				coordY[i] = radio+val[i]*0.25;
			}
		}
		break;
	}
}
////////////// FONDO DEGRADADO
function degradado(){
	if(alfaIntro<1)
		alfaIntro+=0.005;
	for(var y=0; y<=height; y++){
		stroke(noise(frameCount*0.005)*100, 50, 50-y*filaDeg/2, alfaIntro);
		line(0,y,width,y-noise(frameCount*0.0025)*5);
	}
}

function simulaDatos(){
	alfa = nf(noise(frameCount*0.01),1,2);
	beta = nf(noise(frameCount*0.018),1,2);
	gamma = nf(noise(frameCount*0.019),1,2);
	delta = nf(noise(frameCount*0.05),1,2);
	theta = nf(noise(frameCount*0.0315),1,2);
	conc = nf(noise(frameCount*0.02),1,2);
	med = nf(noise(frameCount*0.056),1,2);
	gsr = nf(noise(frameCount*0.00086),1,2);
	BPM = int(50+noise(second()*0.25)*50);

	val[0] = alfa;
	val[1] = beta;
	val[2] = gamma;
	val[3] = delta;
	val[4] = theta;
	val[5] = conc;
	val[6] = med;
	val[7] = gsr;
	val[8] = BPM;

 	freqS = 440+theta*150;

 	if(BPM>80){
 		gateS=1;
 	} else {
 		gateS=0;
 	}	

}
function windowResized() {
	resizeCanvas(windowWidth, windowHeight);
	filaDeg = 100/height;
	pX = width/2;
	pY = height/2;
	radio = height/5;
}

function keyPressed(){
	if(keyCode === RIGHT_ARROW){
		grafica++;
		grafica=grafica%numGraficas;
	}
	if(keyCode === LEFT_ARROW){
		grafica--;
		if(grafica<0)
			grafica = numGraficas-1;
	}
}

function cambiaGraph(){
	grafica++;
	grafica=grafica%numGraficas;
}

// Triggers a note whenever the mouse is clicked.
var synth = flock.synth({
    synthDef: {
        ugen: "flock.ugen.sinOsc",
        freq: freqS,
        mul: 0.25
    }
});