import { mapManager } from "./map.js";
import { spriteManager } from "./spriteManager.js";
import { createSoldier } from "./objects.js";
import { eventsManager } from "./events.js";
import { gameManager } from "./game.js";

let canvas = document.getElementById('gameCanvas');
export let ctx = canvas.getContext('2d');

let game = gameManager;
export let gameStarted = false;

function preloadGame() {
    mapManager.loadMap("map2.json", "mapSrc");
    spriteManager.loadAtlas("mapSrc/sprites.json", "mapSrc/spritesheet.png");
    eventsManager.setup();
}

function initializeGame() {
    mapManager.parseEntities();
    mapManager.draw(ctx);
    game.initPlayer(createSoldier(), 100, 100);
    game.gameCycle(2);
    gameStarted = true;

    game.waitForGameOver().then((data) => {
        gameStarted = false;
        console.log(data);
        preloadGame();
    });
}

preloadGame();

document.addEventListener('DOMContentLoaded', function() {
    document.getElementById("user").innerText = `Игрок ${localStorage.getItem("currentUser")}`;
    
    document.getElementById("startGame").addEventListener('click', () => {
        if (gameStarted){
            return;
        }
        mapManager.waitForLoad().then(() => {
            initializeGame();
        });
    });
    
    document.getElementById("endGame").addEventListener('click', () => {
        game.gameOver();
    });
});