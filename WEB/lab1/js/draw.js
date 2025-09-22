import {WIDTH_GROUND, HEIGTH_GROUND, BLOCK_SIZE, shapes, rotates, ADD_POINTS, colors} from "./utils.js";

export function drawNextShape(shape, shapes){
    let shapeMatr = shapes[shape]["firstRot"];
    const canvas = document.getElementById("nextShape");
    let ctx = canvas.getContext("2d");
    ctx.clearRect(0, 0, canvas.width, canvas.height);
    for (let y = 0; y < shapeMatr.length; y++){
        for (let x = 0; x < shapeMatr[y].length; x++){
            ctx.fillStyle = shapeMatr[y][x] === 0 ? colors[0] : colors[shape + 1];
            ctx.fillRect(x * BLOCK_SIZE, y * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE);
            ctx.strokeRect(x * BLOCK_SIZE, y * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE);
        }
    }
}

export function drawGround(ground){
    const canvas = document.getElementById("mainCanv");
    let ctx = canvas.getContext("2d");
    ctx.clearRect(0, 0, canvas.width, canvas.height);
    for (let y = 0; y < HEIGTH_GROUND; y++){
        for (let x = 0; x < WIDTH_GROUND; x++){
            ctx.fillStyle = colors[ground[y][x]];
            ctx.fillRect(x * BLOCK_SIZE, y * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE);
            ctx.strokeRect(x * BLOCK_SIZE, y * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE);
        }
    }
}