document.getElementById('loginUser').addEventListener('submit', function(e) {
    e.preventDefault();
    if (localStorage.getItem('records') === null){
        localStorage.setItem('records', JSON.stringify({}));
    }
    const username = document.getElementById('user').value;
    const usersRecords = JSON.parse(localStorage.getItem('records'));
    if (!(username in usersRecords)){
        usersRecords[username] = 0;
    }
    localStorage.setItem('records', JSON.stringify(usersRecords));
    localStorage.setItem('currentUser', username);
    window.location.href = '/game';
});