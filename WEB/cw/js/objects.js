import { spriteManager } from "./spriteManager.js";

export let Entity = {
    pos_x: 0, pos_y: 0,
    size_x: 0, size_y: 0,
    extend: function(extendProto){
        let object = Object.create(this);
        for (let property in extendProto){
            if (this.hasOwnProperty(property) || typeof object[property] === 'undefined'){
                object[property] = extendProto[property];
            }
        }
        return object;
    }
};

export let Soldier = Entity.extend({
    lifetime: 5,
    move_x: 0, move_y: 0,
    currentState: "normal_right",
    speed: 5,
    isJump: false,
    isFall: false,
    draw: function(ctx){
        spriteManager.drawSprite(ctx, this.currentState, this.pos_x, this.pos_y);
    },
    jumpRightArgs: {dx: 10, dy: -15},
    jumpLeftArgs: {dx: -10, dy: -15},

    changeState: function(){
        if (this.move_x === 1){
            this.currentState = "run_right";
        }
        else if (this.move_x === -1){
            this.currentState = "run_left";
        }
        else{
            if (this.currentState === "run_left" || this.currentState === "normal_left"){
                this.currentState = "normal_left";
            }
            else{
                this.currentState = "normal_right";
            }
        }
    }
});

export let EnemyRunner = Entity.extend({
    move_x: 0, move_y: 0,
    currentState: "enemy_run",
    speed: 5,
    isFall: false,
    waitNextFire: false,
    draw: function(ctx){
        spriteManager.drawSprite(ctx, this.currentState, this.pos_x, this.pos_y);
    },
});

export function createEnemyRunner(){
    return Entity.extend(EnemyRunner);
}

export let Gun = Entity.extend({
    currentState: "shootgun",
    waitNextFire: false,
    draw: function(ctx){
        spriteManager.drawSprite(ctx, this.currentState, this.pos_x, this.pos_y);
    },
});

export function createGun(){
    return Entity.extend(Gun);
}

export let Fire = Entity.extend({
    move_x: 0, move_y: 0,
    currentState: "fire",
    speed: 5,

    draw: function(ctx){
        spriteManager.drawSprite(ctx, this.currentState, this.pos_x, this.pos_y);
    }
});

export function createFire(){
    return Entity.extend(Fire);
}