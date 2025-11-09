import { mapManager } from "./map.js";
import { createFire, createEnemyRunner, createGun } from "./objects.js";
import { eventsManager } from "./events.js";
import { physicManager } from "./physic.js";
import { enemiesPositionsLevel1, gunsPositionsLevel1, emptyCell, desappearingCell, enemiesPositionsLevel2, gunsPositionsLevel2 } from "./utils.js";
import { ctx } from "./app.js"

export let gameManager = {
    Fires: [],
    Guns: [],
    gunsPositions: [],
    Enemies: [],
    enemiesPositions: [],
    points: 0,
    player: null,
    isBonus: false,
    gameInterval: null,
    gameOverPromise: null,
    gameOverResolve: null,

    initPlayer: function(obj, start_x, start_y) {
        this.player = obj;
        this.player.pos_x = start_x;
        this.player.pos_y = start_y;
    },

    initEnemies: function(){
        for (let i = 0; i < this.enemiesPositions.length; i++){
            let enemy = createEnemyRunner();
            enemy.pos_x = this.enemiesPositions[i].x;
            enemy.pos_y = this.enemiesPositions[i].y;
            let enemyInterval = setInterval(() => {
                physicManager.updateWalk(enemy);
                if (enemy.pos_x - this.player.pos_x <= 500 && enemy.pos_x - this.player.pos_x >= 0){
                    enemy.move_x = -1;
                    enemy.currentState = "enemy_run_left";
                }
                if (this.player.pos_x - enemy.pos_x <= 500 && this.player.pos_x - enemy.pos_x >= 0){
                    enemy.move_x = 1;
                    enemy.currentState = "enemy_run_right";
                }
                if (enemy.pos_x < 10 || enemy.pos_y >= mapManager.mapSize.y - 50){
                    for (let index = 0; index < this.Enemies.length; index++){
                        if (this.Enemies[index].object === enemy){
                            this.Enemies.splice(index, 1);
                            clearInterval(enemyInterval);
                            return;
                        }
                    }
                }
            }, 50);
            this.Enemies.push({object: enemy, interval: enemyInterval});
        }
    },

    initGuns: function(){
        for (let i = 0; i < this.gunsPositions.length; i++){
            let gun = createGun();
            gun.pos_x = this.gunsPositions[i].x;
            gun.pos_y = this.gunsPositions[i].y;
            let gunInterval = setInterval(() => {
                if (Math.sqrt(Math.pow(this.player.pos_x - gun.pos_x, 2) + Math.pow(this.player.pos_y - gun.pos_y, 2)) <= 500){
                    const args = physicManager.findArgsShootgun(this.player.pos_x, this.player.pos_y, gun.pos_x, gun.pos_y);
                    this.addFire(gun, args);
                }
            }, 50);
            this.Guns.push({object: gun, interval: gunInterval});
        }   
    },

    gameCycle: function(level){
        document.getElementById("gameStatus").innerHTML = "Игра началась";
        document.getElementById("points").innerText = `Очки ${this.points}`;

        setTimeout(() => {
            if (level === 1){
                this.enemiesPositions = enemiesPositionsLevel1;
                this.gunsPositions = gunsPositionsLevel1;
            }
            else{
                this.enemiesPositions = enemiesPositionsLevel2;
                this.gunsPositions = gunsPositionsLevel2;
            }
            this.initEnemies();
            this.initGuns();
        }, 100);

        this.gameOverPromise = new Promise((resolve) => {
            this.gameOverResolve = resolve;
        });

        this.gameInterval = setInterval(() => {
            if (this.player.waitNextFire){
                document.getElementById("weaponStatus").innerHTML = "Оружие на перезарядке";
                document.getElementById("weaponStatus").style = "color: red";
            }
            else{
                document.getElementById("weaponStatus").innerHTML = "Оружие готово";
                document.getElementById("weaponStatus").style = "color: green";
            }

            if (this.isBonus){
                document.getElementById("bonus").innerHTML = "Доступны быстрые выстрелы";
            }
            else{
                document.getElementById("bonus").innerHTML = "";
            }

            mapManager.draw(ctx);
            this.player.draw(ctx);
            if (physicManager.intersection(this.player, this.Enemies) !== -1){
                this.gameOver();
            }
            if (physicManager.intersection(this.player, this.Fires) !== -1){
                this.gameOver();
            }
            for (let i = 0; i < this.Guns.length; i++){
                this.Guns[i].object.draw(ctx);
            }
            for (let i = 0; i < this.Enemies.length; i++){
                this.Enemies[i].object.draw(ctx);
            }
            mapManager.centerAt(this.player.pos_x, this.player.pos_y);
            physicManager.updateWalk(this.player);
            if (eventsManager.action['fire'] && !this.player.waitNextFire){
                const args = {move_x: 0, move_y: 0};
                if (this.player.currentState === "normal_right" || this.player.currentState === "run_right" || this.player.currentState === "shoot_up_right"){
                    args.move_x = 1;
                }
                else{
                    args.move_x = -1;
                }
                if (this.player.isUp){
                    args.move_y = -1;
                }
                this.addFire(this.player, args);
            }
            if (eventsManager.action['jump']){
                this.player.isJump = true;
                return;
            }

            if (eventsManager.action['lookUp']){
                this.player.isUp = true;
            }
            else{
                this.player.isUp = false;
            }

            if (this.player.isJump || this.player.isFall){
                return;
            }
            this.player.move_x = eventsManager.action['runRight'] ? 1 : (eventsManager.action['runLeft'] ? -1 : 0);
            this.player.changeState();
        }, 50);
    },

    addFire: function(obj, args){
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
        if (fire.shooter !== "shootgun" && this.isBonus){
            timeInterval = 500;
        }
        
        let flightInterval = setInterval(() => {
            physicManager.updateFly(fire);
            fire.draw(ctx);

            let indexIntersectionEnemy = physicManager.intersection(fire, this.Enemies);
            if (indexIntersectionEnemy !== -1 && fire.shooter !== "shootgun"){
                this.kill(indexIntersectionEnemy, fire, this.Enemies);
                clearInterval(flightInterval);
            }

            let indexIntersectionGun = physicManager.intersection(fire, this.Guns);
            if (indexIntersectionGun !== -1 && fire.shooter !== "shootgun"){
                this.kill(indexIntersectionGun, fire, this.Guns);
                clearInterval(flightInterval);
            }
            
            if (mapManager.getTilesetIdx(fire.pos_x - 5, fire.pos_y + 5) !== emptyCell ||
                mapManager.getTilesetIdx(fire.pos_x + mapManager.tSize.x + 5, fire.pos_y + 5) !== emptyCell){
                for (let index = 0; index < this.Fires.length; index++){
                    if (this.Fires[index].object === fire){
                        this.Fires.splice(index, 1);
                        clearInterval(flightInterval);
                        return;
                    }
                }
            }
        }, 50);
        this.Fires.push({object: fire, interval: flightInterval});
        obj.waitNextFire = true;
        setTimeout(() => {
            obj.waitNextFire = false;
        }, timeInterval);
    }, 
    
    kill: function(i, fire, ArrayObjects){
        this.points += 100;
        document.getElementById("points").innerText = `Очки ${this.points}`;
        clearInterval(ArrayObjects[i].interval);
        ArrayObjects.splice(i, 1);
        for (let index = 0; index < this.Fires.length; index++){
            if (this.Fires[index].object === fire){
                this.Fires.splice(index, 1);
                break;
            }
        }
        if (this.points == 500){
            this.isBonus = true;
            setTimeout(() => {
                this.isBonus = false;
            }, 5000);
        }
    },

    gameOver: function(){
        for (let i = 0; i < this.Fires.length; i++){
            clearInterval(this.Fires[i].interval);
        }
        for (let i = 0; i < this.Enemies.length; i++){
            clearInterval(this.Enemies[i].interval);
        }
        for (let i = 0; i < this.Guns.length; i++){
            clearInterval(this.Guns[i].interval);
        }
        clearInterval(this.gameInterval);
        setTimeout(() => {
            this.Fires = [];
            this.Enemies = [];
            this.Guns = [];
            this.points = 0;
            this.player = null;
            this.isBonus = false;
            document.getElementById("gameStatus").innerHTML = "Game over";
            this.gameInterval = null;
            mapManager.clearMap();

            if (this.gameOverResolve) {
                this.gameOverResolve({points: this.points });
            }
        }, 100);
    },

    waitForGameOver: function() {
        return this.gameOverPromise;
    }
};
