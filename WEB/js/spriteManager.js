import { mapManager } from "./map.js";

export let spriteManager = {
    image: new Image(),
    sprites: new Array(),
    imgLoaded: false,
    jsonLoaded: false,

    loadAtlas: function(atlasJson, atlasImg){
        let request = new XMLHttpRequest();
        request.onreadystatechange = function(){
            if (request.readyState === 4 && request.status === 200){
                spriteManager.parseAtlas(request.responseText);
            }
        };
        request.open("GET", atlasJson, true);
        request.send();
        this.loadImg(atlasImg);
    },

    loadImg: function(imgName){
        this.image.onload = function(){
            spriteManager.imgLoaded = true;
        };
        this.image.src = imgName;
    },

    parseAtlas: function(atlasJSON){
        let atlas = JSON.parse(atlasJSON);
        for (let name in atlas.frames){
            let frame = atlas.frames[name].frame;
            this.sprites.push({name: name, x: frame.x, y: frame.y, w: frame.w, h: frame.h});
        }
        this.jsonLoaded = true;
    },

    drawSprite(ctx, name, x, y){
        if (!this.imgLoaded || !this.jsonLoaded){
            setTimeout(function() {spriteManager.drawSprite(ctx, name, x, y);}, 100);
        }
        else{
            let sprite = this.getSprite(name);
            if (!mapManager.isVisible(x, y, sprite.w, sprite.h)){
                return;
            }
            x -= mapManager.view.x;
            y -= mapManager.view.y;
            ctx.drawImage(this.image, sprite.x, sprite.y, sprite.w, sprite.h, x, y, sprite.w, sprite.h);
        }
    },

    getSprite: function(name){
        for (let i = 0; i < this.sprites.length; i++){
            let s = this.sprites[i];
            if (s.name === name){
                return s;
            }
        }
        return null;
    }
};