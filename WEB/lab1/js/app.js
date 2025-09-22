import {Game} from "./game.js";

let game = new Game();
game.initGame();

document.addEventListener('DOMContentLoaded', function() {
    document.getElementById("startGame").addEventListener('click', () => {
        game.clearGame();
        game.gameStart();
    });
});

document.addEventListener('DOMContentLoaded', function() {
    document.getElementById("endGame").addEventListener('click', () => {
        game.clearGame();
    });
});