import {WIDTH_GROUND, HEIGTH_GROUND, BLOCK_SIZE, shapes, rotates, ADD_POINTS, colors, levels} from "./utils.js";
import { drawGround, drawNextShape } from "./draw.js";
import { putRecords } from "./infoLoad.js";

export class Game{

    constructor(){
        this.mainGround = [];
        this.clearMetrics();
    }

    clearMetrics(){
        this.posX = 0;
        this.posY = 0;
        this.rotate = 0;
        this.shape = Math.floor(Math.random() * (shapes.length));
        this.nextShape = Math.floor(Math.random() * (shapes.length));
        this.SCORE = 0;
        this.isPaused = false;
        this.gameInterval;
        this.level = 0;
        this.isFinished = true;
    }

    addRecord(score){
        const records = JSON.parse(localStorage.getItem('records'));
        if (score > records[localStorage.getItem('tetris.username')]){
            records[localStorage.getItem('tetris.username')] = score;
        }
        
        localStorage.setItem('records', JSON.stringify(records));
    }

    changeState(){
        let shapeMatr = shapes[this.shape][rotates[this.rotate]];

        let newGround = this.mainGround.map(row => [...row]);
        
        for (let y = 0; y < 4; y++){
            for (let x = 0; x < 4; x++){
                if (this.posY + y >= HEIGTH_GROUND || this.posX + x >= WIDTH_GROUND || 
                    this.posY + y < 0 || this.posX + x < 0 || (shapeMatr[y][x] === 0 && newGround[this.posY + y][this.posX + x] !== 0)){
                    continue;
                }
                newGround[this.posY + y][this.posX + x] = shapeMatr[y][x] * (this.shape + 1);
            }
        }
        drawGround(newGround);
    }

    initGame(){
        for (let i = 0; i < HEIGTH_GROUND; i++){
            this.mainGround.push(Array.from({length: WIDTH_GROUND}, () => 0));
        };
        document.getElementById("score").textContent = this.SCORE;
        document.getElementById("level").textContent = this.level + 1;
        drawGround(this.mainGround);
        this.eventListener();
    }

    gameOver(){
        this.isFinished = true;
        document.getElementById("gameOver").textContent = "Game Over";
        document.getElementById("nextShape").innerHTML = "";
        clearInterval(this.gameInterval);
        this.addRecord(this.SCORE);
    }

    clearGame(){
        document.getElementById("gameOver").innerHTML = "";
        document.getElementById("nextShape").innerHTML = "";
        this.mainGround = [];
        for (let i = 0; i < HEIGTH_GROUND; i++){
            this.mainGround.push(Array.from({length: WIDTH_GROUND}, () => 0));
        };
        drawGround(this.mainGround);
        clearInterval(this.gameInterval);
        this.clearMetrics();
        putRecords();
    }

    checkShape(backPosition, posX, posY){
        let shapeMatr = shapes[this.shape][rotates[this.rotate]];
        for (let y = 0; y < 4; y++){
            for (let x = 0; x < 4; x++){
                if (shapeMatr[y][x] !== 0 &&
                    (posY + y >= HEIGTH_GROUND || posX + x >= WIDTH_GROUND || posY + y < 0 || posX + x < 0 || this.mainGround[posY + y][posX + x] !== 0)){
                    backPosition();
                    return true;
                }
            }
        }
        return false;
    }

    eventListener(){
        document.addEventListener("keydown", (event) => {
            if (this.isFinished)
                return;

            if (event.key === "ArrowLeft" && this.posX > 0){
                this.posX--;
                this.checkShape(() => {this.posX++}, this.posX, this.posY);
            }
            else if (event.key === "ArrowRight" && this.posX < WIDTH_GROUND - 1){
                this.posX++; 
                this.checkShape(() => {this.posX--}, this.posX, this.posY);
            }
            else if (event.key === "ArrowUp"){
                this.rotate = this.rotate >= 3 ? 0 : this.rotate + 1;
                this.checkShape(() => {this.rotate = this.rotate === 0 ? 3 : this.rotate - 1;}, this.posX, this.posY);
            }
            else if (event.key === "ArrowDown"){
                this.isPaused = true;
                for (let indexY = this.posY; indexY < HEIGTH_GROUND; indexY++){
                    if (this.checkShape(() => {}, this.posX, indexY + 1)) {
                        this.isPaused = false;
                        this.posY = indexY;
                        break;
                    }
                }
            }
            this.changeState();
        });
    }

    gameStart(){
        this.isFinished = false;
        this.gameInterval = setInterval(() => {this.gameCycle();}, levels[this.level]);
    }

    gameCycle(){
        if (this.SCORE >= 800 * (this.level + 1) && this.level < levels.length - 1){
            ++this.level;
            clearInterval(this.gameInterval);
            this.gameInterval = setInterval(() => {this.gameCycle();}, levels[this.level]);
        }

        document.getElementById("score").textContent = this.SCORE;
        document.getElementById("level").textContent = this.level + 1;
        if (this.isPaused)
            return;
        let shapeMatr = shapes[this.shape][rotates[this.rotate]];
        drawNextShape(this.nextShape, shapes);
        this.changeState();

        let isDown = this.checkShape(()=>{}, this.posX, this.posY + 1);
        
        if (isDown){
            for (let y = 0; y < 4; y++){
                for (let x = 0; x < 4; x++){
                    if (this.posY + y >= HEIGTH_GROUND || this.posX + x >= WIDTH_GROUND || (shapeMatr[y][x] === 0 && this.mainGround[this.posY + y][this.posX + x] !== 0)){
                        continue;
                    }
                    this.mainGround[this.posY + y][this.posX + x] = shapeMatr[y][x] * (this.shape + 1);
                }
            }
            this.posX = 0;
            this.posY = 0;
            this.shape = this.nextShape;
            this.nextShape = Math.floor(Math.random() * (shapes.length));
            this.rotate = 0;
            if (this.checkShape(()=>{}, this.posX, this.posY)){
                this.gameOver();
                return;
            }

            let index = HEIGTH_GROUND - 1;
            let countLines = -1;
            while (index >= 1){
                if (this.mainGround[index].every((element) => {return element !== 0})){
                    this.mainGround = [
                        Array.from({length: WIDTH_GROUND}, () => 0),
                        ...this.mainGround.slice(0, index),
                        ...this.mainGround.slice(index + 1)
                    ];
                    countLines = countLines === ADD_POINTS.length - 1 ? ADD_POINTS.length - 1 : countLines + 1;
                    continue;
                }
                index--;
            }
            if (countLines !== -1){
                this.SCORE += ADD_POINTS[countLines];
            }
            if (this.mainGround[0].find(((element) => {return element !== 0})) !== undefined){
                this.gameOver();
                return;
            }
        }
        else{
            this.posY++;
        }
    }
}