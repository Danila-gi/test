import {WIDTH_GROUND, HEIGTH_GROUND, BLOCK_SIZE, shapes, rotates, ADD_POINTS, colors} from "./utils.js";

export function drawNextShape(shape, shapes) {
    let shapeMatr = shapes[shape]["firstRot"];
    const container = document.getElementById("nextShape");
    
    container.innerHTML = '';
    
    const cols = shapeMatr[0].length;
    const rows = shapeMatr.length;
    
    for (let y = 0; y < rows; y++) {
        for (let x = 0; x < cols; x++) {
            if (shapeMatr[y][x] !== 0) {
                const block = document.createElement('div');
                block.style.position = 'absolute';
                block.style.width = BLOCK_SIZE + 'px';
                block.style.height = BLOCK_SIZE + 'px';
                block.style.left = (x * BLOCK_SIZE) + 'px';
                block.style.top = (y * BLOCK_SIZE) + 'px';
                block.style.backgroundColor = colors[shape + 1];
                block.style.border = '1px solid rgba(0, 0, 0, 0.3)';
                block.style.boxSizing = 'border-box';
                
                container.appendChild(block);
            }
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