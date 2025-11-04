const http = require('http');
const fs = require('fs');
const path = require('path');
const url = require('url');

const port = 3000;

const mimeTypes = {
  '.html': 'text/html',
  '.js': 'text/javascript',
  '.css': 'text/css',
  '.png': 'image/png',
  '.jpg': 'image/jpeg',
  '.gif': 'image/gif',
  '.json': 'application/json',
  '.tsx': 'text/plain'
};

const server = http.createServer((req, res) => {
  const parsedUrl = url.parse(req.url);
  let pathname = parsedUrl.pathname;
    
  // Если запрос к корню, отдаем index.html
  if (pathname === '/') {
    pathname = '/index.html';
  }
  
  // Убираем начальный слеш
  let filePath = pathname.substring(1);
  
  // Пробуем найти файл в разных местах
  const possiblePaths = [
    filePath,                            // прямо по пути
    path.join('js', filePath),           // в папке js
    path.join('js', pathname.substring(1)) // если pathname начинается с /
  ];
  
  let foundPath = null;
  
  // Проверяем существование файла
  for (const tryPath of possiblePaths) {
    const fullPath = path.join(__dirname, tryPath);
    if (fs.existsSync(fullPath)) {
      foundPath = fullPath;
      break;
    }
  }
  
  // Если файл не найден
  if (!foundPath) {
    res.statusCode = 404;
    res.end('File not found');
    return;
  }
  
  // Определяем MIME-тип
  const ext = path.extname(foundPath);
  const mimeType = mimeTypes[ext] || 'text/plain';
  
  // Читаем и отдаем файл
  fs.readFile(foundPath, (err, data) => {
    if (err) {
      res.statusCode = 500;
      res.end('Server error');
      return;
    }
    
    res.setHeader('Content-Type', mimeType);
    
    // Добавляем CORS заголовки если нужно
    res.setHeader('Access-Control-Allow-Origin', '*');
    
    res.end(data);
  });
});

server.listen(port, () => {
  console.log(`Server running at http://localhost:${port}/`);
});