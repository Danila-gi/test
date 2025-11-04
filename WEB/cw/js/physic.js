import { mapManager } from "./map.js";
import { spriteManager } from "./spriteManager.js";
import { Entity, Soldier } from "./objects.js";

export let physicManager = {
    jumpArgs: {dx: 10, dy: -15},
    fallDownArgs: {dy: 5},

    update: function(obj){
        if (obj.isJump && !obj.isFall){
            this.jump(obj);
            return;
        }
        obj.isJump = false;
        if (mapManager.getTilesetIdx(obj.pos_x + mapManager.tSize.x, obj.pos_y + mapManager.tSize.y + 2) === 1 || obj.isFall){
            this.fallDown(obj);
        }
        if (obj.move_x === 0 && obj.move_y === 0){
            return;
        }

        if (obj.move_x === -1 && mapManager.getTilesetIdx(obj.pos_x - 5, obj.pos_y + 5) !== 1 ||
            obj.move_x === 1 && mapManager.getTilesetIdx(obj.pos_x + mapManager.tSize.x + 5, obj.pos_y + 5) !== 1 || obj.isFall){
            return;
        }

        let newX = obj.pos_x + Math.floor(obj.move_x * obj.speed);

        obj.pos_x = newX;
    },

    fallDown: function(obj){
        obj.isFall = true;
            
        let newY = obj.pos_y + this.fallDownArgs.dy;
        obj.pos_y = newY;
        this.fallDownArgs.dy += 0.2;
        
        if (mapManager.getTilesetIdx(obj.pos_x, obj.pos_y + mapManager.tSize.y + 1) !== 1){
            for (let y = obj.pos_y; y >= 0; y--){
                if (mapManager.getTilesetIdx(obj.pos_x, y + mapManager.tSize.y + 1) === 1){
                    obj.pos_y = y;
                    obj.isFall = false;
                    this.clearFallDown();
                    break;
                }
            }
        }
    },

    jump: function(obj){
        if (obj.move_x === 0 && obj.move_y === 0){
            this.jumpArgs.dx = 0;
        }
        if (obj.currentState === "normal_right" || obj.move_x === 1){
            const isSideEmpty = mapManager.getTilesetIdx(obj.pos_x + mapManager.tSize.x + 15, obj.pos_y) === 1;  
            if (isSideEmpty){
                obj.pos_x += this.jumpArgs.dx;
            }
        }
        else if (obj.currentState === "normal_left" || obj.move_x === -1){
            const isSideEmpty = mapManager.getTilesetIdx(obj.pos_x - 15, obj.pos_y) === 1;
            if (isSideEmpty){
                obj.pos_x -= this.jumpArgs.dx;
            }
        }
        const isUpEmpty = mapManager.getTilesetIdx(obj.pos_x, obj.pos_y - 15) === 1; 
        if (isUpEmpty){
            obj.pos_y += this.jumpArgs.dy;
        }
        else{
            this.jumpArgs.dy = 1;
            obj.pos_y += this.jumpArgs.dy;
        }
        this.jumpArgs.dy += 1; 
        if (mapManager.getTilesetIdx(obj.pos_x  + mapManager.tSize.x / 2, obj.pos_y + mapManager.tSize.y) !== 1){
            for (let y = obj.pos_y; y >= 0; y--){
                if (mapManager.getTilesetIdx(obj.pos_x + mapManager.tSize.x / 2, y + mapManager.tSize.y) === 1){
                    obj.pos_y = y;
                    break;
                }
            }
            this.clearJump();
            obj.isJump = false;
        }
    },

    findArgsShootgun(x1, y1, x2, y2){
        const length = Math.sqrt(Math.pow(x1 - x2, 2) + Math.pow(y1 - y2, 2));
        const move_x = (x1 - x2) / length;
        const move_y = Math.abs(y1 - y2) / length;
        return {move_x: move_x, move_y: move_y};
    },

    clearFallDown: function(){
        this.fallDownArgs.dy = 5;
    },

    clearJump: function(){
        this.jumpArgs = {dx: 10, dy: -15};
    }
}