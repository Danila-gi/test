import { mapManager } from "./map.js";
import { spriteManager } from "./spriteManager.js";
import { Entity, Soldier } from "./objects.js";

let canvas = document.getElementById('gameCanvas');
let ctx = canvas.getContext('2d');

let gameInterval;
let fallInterval;

mapManager.loadMap("./map.json");
spriteManager.loadAtlas("./atlas.json", "./objects.png");

mapManager.parseEntities();

const keysForJump = {
    space: false,
    arrowRight: false,
    arrowLeft: false,
};

document.body.addEventListener("keydown", (event) => {
    if (keysForJump.space){
        return;
    }
    const key = event.key;
    if (key === 'ArrowLeft'){
        if (mapManager.getTilesetIdx(Soldier.pos_x - 5, Soldier.pos_y + 5) !== 1){
            return;
        }
        Soldier.moveLeft();
        keysForJump.arrowLeft = true;
    }
    if (key === 'ArrowRight'){
        if (mapManager.getTilesetIdx(Soldier.pos_x + mapManager.tSize.x + 5, Soldier.pos_y + 5) !== 1){
            return;
        }
        Soldier.moveRight();
        keysForJump.arrowRight = true;
    }
    if (key === ' '){
        keysForJump.space = true;
        clearInterval(gameInterval);
        clearInterval(fallInterval);
        if (Soldier.currentState === "normal_right" || keysForJump.arrowRight){
            Soldier.pos_y -= 50;
            const jumpRightInterval = setInterval(function(){
                const isSideEmpty = mapManager.getTilesetIdx(Soldier.pos_x + mapManager.tSize.x + 15, Soldier.pos_y) === 1;
                const isUpEmpty = mapManager.getTilesetIdx(Soldier.pos_x, Soldier.pos_y - 15) === 1;   
                Soldier.jumpRight(isSideEmpty, isUpEmpty); 
                if (mapManager.getTilesetIdx(Soldier.pos_x, Soldier.pos_y + mapManager.tSize.y) !== 1){
                    for (let y = Soldier.pos_y; y >= 0; y--){
                        if (mapManager.getTilesetIdx(Soldier.pos_x, y + mapManager.tSize.y) === 1){
                            Soldier.pos_y = y;
                            break;
                        }
                    }
                    keysForJump.arrowRight = false;
                    keysForJump.space = false;
                    Soldier.endJump();
                    clearInterval(jumpRightInterval);
                    gameCycle();
                }
                mapManager.draw(ctx);
                Soldier.draw(ctx);
                mapManager.centerAt(Soldier.pos_x, Soldier.pos_y);
            }, 50);
        }
        else if (Soldier.currentState === "normal_left" || keysForJump.arrowLeft){
            Soldier.pos_y -= 50;
            const jumpLeftInterval = setInterval(function(){
                const isSideEmpty = mapManager.getTilesetIdx(Soldier.pos_x - 15, Soldier.pos_y) === 1;
                const isUpEmpty = mapManager.getTilesetIdx(Soldier.pos_x, Soldier.pos_y - 15) === 1;   
                Soldier.jumpLeft(isSideEmpty, isUpEmpty); 
                if (mapManager.getTilesetIdx(Soldier.pos_x, Soldier.pos_y + mapManager.tSize.y) !== 1){
                    for (let y = Soldier.pos_y; y >= 0; y--){
                        if (mapManager.getTilesetIdx(Soldier.pos_x, y + mapManager.tSize.y) === 1){
                            Soldier.pos_y = y;
                            break;
                        }
                    }
                    keysForJump.arrowLeft = false;
                    keysForJump.space = false;
                    Soldier.endJump();
                    clearInterval(jumpLeftInterval);
                    gameCycle();
                }
                mapManager.draw(ctx);
                Soldier.draw(ctx);
                mapManager.centerAt(Soldier.pos_x, Soldier.pos_y);
            }, 50);
        }
        else{
            keysForJump.space = false;
            gameCycle();
        }
    }
});

mapManager.waitForLoad().then(() => {
    mapManager.parseEntities();
    mapManager.draw(ctx);
    
    let x = 200;
    let y = 200;
    Soldier.pos_x = x;
    Soldier.pos_y = y;
    //console.log(Soldier.pos_x, Soldier.pos_y + mapManager.tSize.y);
    //console.log(mapManager.getTilesetIdx(Soldier.pos_x, Soldier.pos_y + mapManager.tSize.y));

    //Soldier.draw(ctx);
    
    fallHero();
});

function fallHero(){
    fallInterval = setInterval(function() {
        mapManager.draw(ctx);
        
        Soldier.moveDown();
        
        if (mapManager.getTilesetIdx(Soldier.pos_x, Soldier.pos_y + mapManager.tSize.y) !== 1){
            for (let y = Soldier.pos_y; y >= 0; y--){
                if (mapManager.getTilesetIdx(Soldier.pos_x, y + mapManager.tSize.y) === 1){
                    Soldier.pos_y = y;
                    break;
                }
            }
            gameCycle();
            clearInterval(fallInterval);
        }
        
        Soldier.draw(ctx);
        mapManager.centerAt(Soldier.pos_x, Soldier.pos_y);
        
    }, 1);
}

function gameCycle(){
    gameInterval = setInterval(function(){
        mapManager.draw(ctx);
        Soldier.draw(ctx);
        mapManager.centerAt(Soldier.pos_x, Soldier.pos_y);
        if (Soldier.currentState === "run_right" || Soldier.currentState === "normal_right"){
            Soldier.currentState = "normal_right";
        }
        else if (Soldier.currentState === "run_left" || Soldier.currentState === "normal_left"){
            Soldier.currentState = "normal_left";
        }
        if (mapManager.getTilesetIdx(Soldier.pos_x + mapManager.tSize.x, Soldier.pos_y + mapManager.tSize.y + 1) === 1){
            fallHero();
            clearInterval(gameInterval);
        }
    }, 50);
}