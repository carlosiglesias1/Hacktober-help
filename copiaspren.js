const readlineSync = require("readline-sync")

var sujeto = ["Juan", "Pedro", "Josefa", "Laura", "Hideo Kojima", "Ramón", "Un grupo de vietnamitas", "El cuerpo de estudiantes", "El equipo directivo", "Ese de ahí", "Esa de ahí", "Pitbull", "Armando Pérez", "Venancio", "Un programador"]
var verbo = ["come", "salta", "baila", "canta", "saltaba", "comía", "bailaba", "estudia", "estudiará", "estudiaba", "saltará", "bailará", "cantará"]
var cc = ["en el parque", "en su casa", "a la tarde", "al caer el sol", "en el tren", "en la sala de reuniones", "en vietnam", "en Cataluña", "en su país", "porque sí", "porque aprobó", "porque le dejan"]

var frases = [];

while (true) {
    console.log("Categoría conocida:\n1.Sujeto\n2.Verbo (funciona mejor en presente)\n3.Complemento circunstancial");
    var categ = readlineSync.question('>');
    if(categ != 1 && categ != 2 && categ != 3){console.log("Error, por favor selecciona una categoría válida");}
    else{break;}
}

console.log("Texto a utilizar:");
var palabra = readlineSync.question('>');

while(true){
    console.log("Veces:")
    
    switch(categ){
        case "1":
            var vMax = verbo.length*cc.length
            break;
        case "2":
            var vMax = sujeto.length*cc.length;
            break
        case "3":
            var vMax = sujeto.length*verbo.length;
            break;
    }

    console.log("Max: "+ vMax)
    var veces = readlineSync.question(">");

    if(veces > vMax){console.log("Error, por favor selecciona un número menor que " + vMax);}
    else{break;}
}

while(veces > 0){
    var verboR = randomItem(verbo);
    var sujetoR = randomItem(sujeto);
    var ccR = randomItem(cc);

    switch(categ){
        case "1":
            var frase = (palabra + " " + verboR + " " + ccR + ".");
            break;
        case "2":
            var frase = (sujetoR + " " + palabra + " " + ccR + ".");
            break
        case "3":
            var frase = (sujetoR + " " + verboR + " " + palabra + ".");
            break;
        default:
            console.log("Algo no funciona");
            break;
    }

    if(frases.includes(frase)){
        //console.log("repe");
    }
    else{
        frases.push(frase);
        console.log(frase);
        veces--
    }
}

console.log(frases.length)

function randomItem(list) {
    return list[Math.floor((Math.random()*list.length))];
}