import {IShape, OShape, TShape, LShape, JShape, ZShape, SShape} from "./utils.js";

const WIDTH_GROUND = 10;
const HEIGTH_GROUND = 20;
const BLOCK_SIZE = 20;
const shapes = [IShape, OShape, TShape, LShape, JShape, ZShape, SShape];
const rotates = ["firstRot", "secondRot", "thirdRot", "fourthRot"];
const ADD_POINTS = [100, 300, 700, 1500];
const colors = ["#ffffff", "#ff0000", "#00ff00", "#0000ff", "#ffff00", "#ff00ff", "#00ffff", "#8b00ff"];
let mainGround = [];

function drawNextShape(shape){
    let shapeMatr = shapes[shape]["firstRot"];
    const canvas = document.getElementById("nextShape");
    let ctx = canvas.getContext("2d");
    ctx.clearRect(0, 0, canvas.width, canvas.height);
    for (let y = 0; y < shapeMatr.length; y++){
        for (let x = 0; x < shapeMatr[y].length; x++){
            ctx.fillStyle = shapeMatr[y][x] === 0 ? colors[0] : colors[shape + 1];
            ctx.fillRect(x * BLOCK_SIZE, y * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE);
            ctx.strokeRect(x * BLOCK_SIZE, y * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE);
        }
    }
}

function drawGround(ground){
    const canvas = document.getElementById("mainCanv");
    let ctx = canvas.getContext("2d");
    ctx.clearRect(0, 0, canvas.width, canvas.height);
    for (let y = 0; y < HEIGTH_GROUND; y++){
        for (let x = 0; x < WIDTH_GROUND; x++){
            ctx.fillStyle = colors[ground[y][x]];
            ctx.fillRect(x * BLOCK_SIZE, y * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE);
            ctx.strokeRect(x * BLOCK_SIZE, y * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE);
        }
    }
}

function changeState(posX, posY, rotate, shape){
    let shapeMatr = shapes[shape][rotates[rotate]];

    let newGround = mainGround.map(row => [...row]);
    
    for (let y = 0; y < 4; y++){
        for (let x = 0; x < 4; x++){
            if (posY + y >= HEIGTH_GROUND || posX + x >= WIDTH_GROUND || 
                posY + y < 0 || posX + x < 0 || (shapeMatr[y][x] === 0 && newGround[posY + y][posX + x] !== 0)){
                continue;
            }
            newGround[posY + y][posX + x] = shapeMatr[y][x] * (shape + 1);
        }
    }
    drawGround(newGround);
}

function initGame(){
    clearGame();
    document.getElementById("score").innerHTML = "<p>"+0+"</p>";
    drawGround(mainGround);
}

function clearGame(){
    document.getElementById("gameOver").innerHTML = "";
    mainGround = [];
    for (let i = 0; i < HEIGTH_GROUND; i++){
        mainGround.push(Array.from({length: WIDTH_GROUND}, () => 0));
    };
}

function gameCycle(){
    let posX = 0;
    let posY = 0;
    let rotate = 0;
    let shape = Math.floor(Math.random() * (shapes.length));
    let nextShape = Math.floor(Math.random() * (shapes.length));
    let SCORE = 0;
    let isPaused = false;

    document.addEventListener("keydown", (event) => {
        if (event.key === "ArrowLeft" && posX > 0){
            posX--;
            let shapeMatr = shapes[shape][rotates[rotate]];
            for (let y = 0; y < 4; y++){
                for (let x = 0; x < 4; x++){
                    if (shapeMatr[y][x] !== 0 &&
                        (posY + y >= HEIGTH_GROUND || posX + x >= WIDTH_GROUND ||
                        posY + y < 0 || posX + x < 0 || mainGround[posY + y][posX + x] !== 0)){
                        posX++;
                        return;
                    }
                }
            }
        }
        else if (event.key === "ArrowRight" && posX < WIDTH_GROUND - 1){
            posX++;
            let shapeMatr = shapes[shape][rotates[rotate]];
            for (let y = 0; y < 4; y++){
                for (let x = 0; x < 4; x++){
                    if (shapeMatr[y][x] !== 0 &&
                        (posY + y >= HEIGTH_GROUND || posX + x >= WIDTH_GROUND ||
                        posY + y < 0 || posX + x < 0 || mainGround[posY + y][posX + x] !== 0)){
                        posX--;
                        return;
                    }
                }
            }
        }
        else if (event.key === "ArrowUp"){
            rotate = rotate >= 3 ? 0 : rotate + 1;
            let shapeMatr = shapes[shape][rotates[rotate]];
            for (let y = 0; y < 4; y++){
                for (let x = 0; x < 4; x++){
                    if (shapeMatr[y][x] !== 0 &&
                        (posY + y >= HEIGTH_GROUND || posX + x >= WIDTH_GROUND ||
                        posY + y < 0 || posX + x < 0 || mainGround[posY + y][posX + x] !== 0)){
                        rotate = rotate === 0 ? 3 : rotate - 1;
                        return;
                    }
                }
            }
        }
        else if (event.key === "ArrowDown"){
            let shapeMatr = shapes[shape][rotates[rotate]];
            isPaused = true;
            for (let indexY = posY; indexY < HEIGTH_GROUND; indexY++){
                for (let y = 0; y < 4; y++){
                    for (let x = 0; x < 4; x++){
                        if (shapeMatr[y][x] !== 0 && (indexY + y === HEIGTH_GROUND - 1 || posX + x >= WIDTH_GROUND || (mainGround[indexY + y + 1][posX + x]) !== 0)){
                            isPaused = false;
                            posY = indexY;
                            return;
                        }
                    }
                }
            }
        }
        changeState(posX, posY, rotate, shape);
    });
    const interval = setInterval(() => {
        document.getElementById("score").innerHTML = "<p>"+SCORE+"</p>";
        if (isPaused)
            return;
        let shapeMatr = shapes[shape][rotates[rotate]];
        drawNextShape(nextShape);
        changeState(posX, posY, rotate, shape);

        let isDown = false;
        for (let y = 0; y < 4; y++){
            for (let x = 0; x < 4; x++){
                if (shapeMatr[y][x] !== 0 && (posY + y === HEIGTH_GROUND - 1 || posX + x >= WIDTH_GROUND || (mainGround[posY + y + 1][posX + x]) !== 0)){
                    isDown = true;
                    break;
                }
            }
            if (isDown){
                break;
            }
        }
         
        if (isDown){
            for (let y = 0; y < 4; y++){
                for (let x = 0; x < 4; x++){
                    if (posY + y >= HEIGTH_GROUND || posX + x >= WIDTH_GROUND || (shapeMatr[y][x] === 0 && mainGround[posY + y][posX + x] !== 0)){
                        continue;
                    }
                    mainGround[posY + y][posX + x] = shapeMatr[y][x] * (shape + 1);
                }
            }
            posX = 0;
            posY = 0;
            shape = nextShape;
            nextShape = (nextShape + 1) % shapes.length;
            rotate = 0;

            let index = HEIGTH_GROUND - 1;
            let countLines = -1;
            while (index >= 1){
                if (mainGround[index].every((element) => {return element !== 0})){
                    mainGround = [
                        Array.from({length: WIDTH_GROUND}, () => 0),
                        ...mainGround.slice(0, index),
                        ...mainGround.slice(index + 1)
                    ];
                    countLines = countLines === ADD_POINTS.length - 1 ? ADD_POINTS.length - 1 : countLines + 1;
                    continue;
                }
                index--;
            }
            if (countLines !== -1){
                SCORE += ADD_POINTS[countLines];
                console.log("SCORE: " + SCORE);
            }
            if (mainGround[0].find(((element) => {return element !== 0})) !== undefined){
                console.log("GAME OVER");
                document.getElementById("gameOver").innerHTML = "<p>Game Over</p>";
                clearInterval(interval);
            }
        }
        else{
            posY++;
        }
    }, 200);
}

initGame();

document.addEventListener('DOMContentLoaded', function() {
    document.getElementById("startGame").addEventListener('click', () => {
        clearGame();
        gameCycle();
    });
});