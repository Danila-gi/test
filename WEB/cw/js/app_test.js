import { mapManager } from "./map.js";
import { spriteManager } from "./spriteManager.js";
import { Soldier, createFire, createEnemyRunner, createGun } from "./objects.js";
import { eventsManager } from "./events.js";
import { physicManager } from "./physic.js";
import { enemiesPositions, gunsPositions } from "./utils.js";

let Fires = [];
let Enemies = [];
let Guns = [];
let points = 0;
let isBonus = false;

let canvas = document.getElementById('gameCanvas');
let ctx = canvas.getContext('2d');

let gameInterval;

mapManager.loadMap("map.json", "mapSrc");
spriteManager.loadAtlas("mapSrc/sprites.json", "mapSrc/spritesheet.png");

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
    fire.pos_x = fire.pos_x + 20 * fire.move_x;
    fire.pos_y = fire.pos_y + 20 * fire.move_y;
    fire.shooter = obj.currentState;
    let timeInterval = 2500;
    if (fire.shooter !== "shootgun" && isBonus){
        timeInterval = 500;
    }
    
    let flightInterval = setInterval(function(){
        physicManager.updateFly(fire);
        fire.draw(ctx);

        let indexIntersectionEnemy = physicManager.intersection(fire, Enemies);
        if (indexIntersectionEnemy !== -1 && fire.shooter !== "shootgun"){
            kill(indexIntersectionEnemy, fire, Enemies);
            clearInterval(flightInterval);
        }

        let indexIntersectionGun = physicManager.intersection(fire, Guns);
        if (indexIntersectionGun !== -1 && fire.shooter !== "shootgun"){
            kill(indexIntersectionGun, fire, Guns);
            clearInterval(flightInterval);
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
    }, 50);
    Fires.push({object: fire, interval: flightInterval});
    obj.waitNextFire = true;
    setTimeout(function(){
        obj.waitNextFire = false;
    }, timeInterval);
}

function kill(i, fire, ArrayObjects){
    points += 100;
    document.getElementById("points").innerText = `Очки ${points}`;
    clearInterval(ArrayObjects[i].interval);
    ArrayObjects.splice(i, 1);
    for (let index = 0; index < Fires.length; index++){
        if (Fires[index].object === fire){
            Fires.splice(index, 1);
            break;
        }
    }
    if (points >= 300){
        isBonus = true;
        setTimeout(function(){
            isBonus = false;
        }, 5000);
    }
}

function initEnemies(){
    for (let i = 0; i < enemiesPositions.length; i++){
        let enemy = createEnemyRunner();
        enemy.pos_x = enemiesPositions[i].x;
        enemy.pos_y = enemiesPositions[i].y;
        let enemyInterval = setInterval(function(){
            physicManager.updateWalk(enemy);
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

function gameOver(){
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

        if (isBonus){
            document.getElementById("bonus").innerHTML = "Доступны быстрые выстрелы";
        }
        else{
            document.getElementById("bonus").innerHTML = "";
        }

        mapManager.draw(ctx);
        Soldier.draw(ctx);
        if (physicManager.intersection(Soldier, Enemies) !== -1){
            gameOver();
        }
        if (physicManager.intersection(Soldier, Fires) !== -1){
            gameOver();
        }
        for (let i = 0; i < Guns.length; i++){
            Guns[i].object.draw(ctx);
        }
        for (let i = 0; i < Enemies.length; i++){
            Enemies[i].object.draw(ctx);
        }
        mapManager.centerAt(Soldier.pos_x, Soldier.pos_y);
        physicManager.updateWalk(Soldier);
        if (eventsManager.action['fire'] && !Soldier.waitNextFire){
            const args = {move_x: 0, move_y: 0};
            if (Soldier.currentState === "normal_right" || Soldier.currentState === "run_right" || Soldier.currentState === "shoot_up_right"){
                args.move_x = 1;
            }
            else{
                args.move_x = -1;
            }
            if (Soldier.isUp){
                args.move_y = -1;
            }
            addFire(Soldier, args);
        }
        if (eventsManager.action['jump']){
            Soldier.isJump = true;
            return;
        }

        if (eventsManager.action['lookUp']){
            Soldier.isUp = true;
        }
        else{
            Soldier.isUp = false;
        }

        if (Soldier.isJump || Soldier.isFall){
            return;
        }
        Soldier.move_x = eventsManager.action['runRight'] ? 1 : (eventsManager.action['runLeft'] ? -1 : 0);
        Soldier.changeState();
    }, 50);
}