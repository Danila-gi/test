function printUserInfo(){
    const name = document.getElementById("user");
    name.textContent = localStorage.getItem('tetris.username');
}