document.getElementById('loginUser').addEventListener('submit', function(e) {
    e.preventDefault(); // отменяется стандартная отправка формы, выполняется весь js код
    if (localStorage.getItem('records') === null){
        localStorage.setItem('records', JSON.stringify({}));
    }
    const username = document.getElementById('username').value;
    const usersRecords = JSON.parse(localStorage.getItem('records'));
    if (!(username in usersRecords)){
        usersRecords[username] = 0;
    }
    localStorage.setItem('records', JSON.stringify(usersRecords));
    localStorage.setItem('tetris.username', username);
    window.location.href = 'game.html';
});