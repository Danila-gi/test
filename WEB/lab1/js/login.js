console.log('Все данные localStorage:', localStorage);

document.getElementById('loginUser').addEventListener('submit', function(e) {
    e.preventDefault();
    const username = document.getElementById('username').value;
    localStorage.setItem('tetris.username', username);
    window.location.href = 'game.html';
});