import { mapManager } from "./map.js";
import { spriteManager } from "./spriteManager.js";
import { Entity, Soldier, Fire, createFire, createEnemyRunner, Gun, createGun } from "./objects.js";
import { eventsManager } from "./events.js";
import { physicManager } from "./physic.js";

let Fires = [];
let Enemies = [];
let Guns = [];
let points = 0;
let enemiesPositions = [
    {x: 1200, y: 200},
    {x: 1900, y: 200},
    {x: 2500, y: 200},
    {x: 3300, y: 200},
    {x: 3400, y: 200},
    {x: 4000, y: 200},
    {x: 4600, y: 200},
]
let gunsPositions = [
    {x: 1500, y: 500},
    {x: 2400, y: 500},
    {x: 3000, y: 550},
    {x: 3500, y: 550},
    {x: 4200, y: 550},
]

let canvas = document.getElementById('gameCanvas');
let ctx = canvas.getContext('2d');

let gameInterval;

mapManager.loadMap("./map.json");
spriteManager.loadAtlas("./sprites.json", "./spritesheet.png");

mapManager.parseEntities();

eventsManager.setup();

mapManager.waitForLoad().then(() => {
    mapManager.parseEntities();
    mapManager.draw(ctx);
    
    let x = 200;
    let y = 200;
    Soldier.pos_x = x;
    Soldier.pos_y = y;
    
    gameCycle();
});

function addFire(obj, args){
    if (obj.waitNextFire){
        return;
    }
    let fire = createFire();
    fire.pos_x = obj.pos_x;
    fire.pos_y = obj.pos_y;
    fire.move_x = args.move_x;
    fire.move_y = args.move_y;
    fire.pos_x = fire.pos_x + 15 * fire.move_x;
    fire.pos_y = fire.pos_y + 15 * fire.move_y;
    
    let flightInterval = setInterval(function(){
        let newX = fire.pos_x + Math.floor(fire.move_x * fire.speed);
        let newY = fire.pos_y + Math.floor(fire.move_y * fire.speed);
        fire.pos_x = newX;
        fire.pos_y = newY;
        fire.draw(ctx);

        for (let i = 0; i < Enemies.length; i++){
            if (Enemies[i].object.pos_y - 15 <= fire.pos_y && 
                Enemies[i].object.pos_y + mapManager.tSize.y + 15 >= fire.pos_y &&
                Enemies[i].object.pos_x <= fire.pos_x && 
                Enemies[i].object.pos_x + mapManager.tSize.x / 2 >= fire.pos_x){
                points += 100;
                document.getElementById("points").innerText = `Очки ${points}`;
                clearInterval(Enemies[i].interval);
                Enemies.splice(i, 1);
                for (let index = 0; index < Fires.length; index++){
                    if (Fires[index].object === fire){
                        Fires.splice(index, 1);
                        break;
                    }
                }
                clearInterval(flightInterval);
            }
        }
        
        if (mapManager.getTilesetIdx(fire.pos_x - 5, fire.pos_y + 5) !== 1 ||
            mapManager.getTilesetIdx(fire.pos_x + mapManager.tSize.x + 5, fire.pos_y + 5) !== 1){
            for (let index = 0; index < Fires.length; index++){
                if (Fires[index].object === fire){
                    Fires.splice(index, 1);
                    break;
                }
            }
            clearInterval(flightInterval);
        }
    }, 25);
    Fires.push({object: fire, interval: flightInterval});
    obj.waitNextFire = true;
    setTimeout(function(){
        obj.waitNextFire = false;
    }, 2500);
}

function initEnemies(){
    for (let i = 0; i < enemiesPositions.length; i++){
        let enemy = createEnemyRunner();
        enemy.pos_x = enemiesPositions[i].x;
        enemy.pos_y = enemiesPositions[i].y;
        let enemyInterval = setInterval(function(){
            physicManager.update(enemy);
            if (enemy.pos_x - Soldier.pos_x <= 500 && enemy.pos_x - Soldier.pos_x >= 0){
                enemy.move_x = -1;
            }
            if (Soldier.pos_x - enemy.pos_x <= 500 && Soldier.pos_x - enemy.pos_x >= 0){
                enemy.move_x = 1;
            }
            if (enemy.pos_x < 10 || enemy.pos_y >= mapManager.mapSize.y - 50){
                for (let index = 0; index < Enemies.length; index++){
                    if (Enemies[index].object === enemy){
                        Enemies.splice(index, 1);
                        clearInterval(enemyInterval);
                        return;
                    }
                }
            }
        }, 50);
        Enemies.push({object: enemy, interval: enemyInterval});
    }
}

function initGuns(){
    for (let i = 0; i < gunsPositions.length; i++){
        let gun = createGun();
        gun.pos_x = gunsPositions[i].x;
        gun.pos_y = gunsPositions[i].y;
        let gunInterval = setInterval(function(){
            if (Math.sqrt(Math.pow(Soldier.pos_x - gun.pos_x, 2) + Math.pow(Soldier.pos_y - gun.pos_y, 2)) <= 500){
                const args = physicManager.findArgsShootgun(Soldier.pos_x, Soldier.pos_y, gun.pos_x, gun.pos_y);
                addFire(gun, args);
            }
        }, 50);
        Guns.push({object: gun, interval: gunInterval});
    }   
}

function gameCycle(){
    initEnemies();
    initGuns();
    gameInterval = setInterval(function(){
        if (Soldier.waitNextFire){
            document.getElementById("weaponStatus").innerHTML = "Оружие на перезарядке";
            document.getElementById("weaponStatus").style = "color: red";
        }
        else{
            document.getElementById("weaponStatus").innerHTML = "Оружие готово";
            document.getElementById("weaponStatus").style = "color: green";
        }
        mapManager.draw(ctx);
        Soldier.draw(ctx);
        for (let i = 0; i < Enemies.length; i++){
            Enemies[i].object.draw(ctx);
            if (Soldier.pos_y - 5 <= Enemies[i].object.pos_y && 
                Soldier.pos_y + mapManager.tSize.y + 5 >= Enemies[i].object.pos_y &&
                Soldier.pos_x <= Enemies[i].object.pos_x && 
                Soldier.pos_x + mapManager.tSize.x / 2 >= Enemies[i].object.pos_x){
                for (let i = 0; i < Fires.length; i++){
                    clearInterval(Fires[i].interval);
                }
                for (let i = 0; i < Enemies.length; i++){
                    clearInterval(Enemies[i].interval);
                }
                document.getElementById("gameStatus").innerHTML = "Game over";
                clearInterval(gameInterval);
            }
        }
        for (let i = 0; i < Guns.length; i++){
            Guns[i].object.draw(ctx);
        }
        for (let i = 0; i < Fires.length; i++){
            if (Soldier.pos_y - 15 <= Fires[i].object.pos_y && 
            Soldier.pos_y + mapManager.tSize.y + 15 >= Fires[i].object.pos_y &&
            Soldier.pos_x <= Fires[i].object.pos_x && 
            Soldier.pos_x + mapManager.tSize.x / 2 >= Fires[i].object.pos_x){
                console.log(Fires[i].object);
                for (let i = 0; i < Fires.length; i++){
                    clearInterval(Fires[i].interval);
                }
                for (let i = 0; i < Enemies.length; i++){
                    clearInterval(Enemies[i].interval);
                }
                for (let i = 0; i < Guns.length; i++){
                    clearInterval(Guns[i].interval);
                }
                document.getElementById("gameStatus").innerHTML = "Game over";
                clearInterval(gameInterval);
            }

        }
        mapManager.centerAt(Soldier.pos_x, Soldier.pos_y);
        physicManager.update(Soldier);
        if (eventsManager.action['fire'] && !Soldier.waitNextFire){
            const args = {move_x: 0, move_y: 0};
            if (Soldier.currentState === "normal_right" || Soldier.currentState === "run_right"){
                args.move_x = 1;
            }
            else{
                args.move_x = -1;
            }
            addFire(Soldier, args);
        }
        if (eventsManager.action['jump']){
            Soldier.isJump = true;
            return;
        }
        if (Soldier.isJump || Soldier.isFall){
            return;
        }
        Soldier.move_x = eventsManager.action['runRight'] ? 1 : (eventsManager.action['runLeft'] ? -1 : 0);
        Soldier.changeState();
    }, 50);
}