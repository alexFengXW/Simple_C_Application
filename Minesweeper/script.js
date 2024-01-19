document.addEventListener("DOMContentLoaded", function() {
    // Images and settings
    const emptyImage = 'url("empty.png")';
    const cellImage = 'url("cell.png")';
    const bombImage = 'url("bomb.png")';
    const flagImage = 'url("flag.png")';
    const notFlagImage = 'url("notFlagImage.png")';
    const victoryImage = 'url("victoryImage.png")';
    const numberImages = [
        'url("empty.png")',
        'url("1.png")',
        'url("2.png")',
        'url("3.png")',
        'url("4.png")'
    ];

    let boardSize;
    let bombCount;
    let flagsCount = 0;
    let board;
    let gameActive = true;
    let flagMode = false;

    function initializeGame() {
        boardSize = parseInt(document.getElementById('boardSizeSelect').value);
        bombCount = Math.floor(boardSize * boardSize * 0.15);
        gameActive = true;
        flagsCount = 0;
        flagMode = false;
        board = createBoard(boardSize);
        addClickHandlers();
        updateBombsLeftDisplay();
        document.getElementById('toggleFlagButton').textContent = 'Toggle Flag Mode';
    }

    function createBoard(size) {
        const board = [];
        const gameBoard = document.getElementById('gameBoard');
        gameBoard.innerHTML = '';
        gameBoard.style.gridTemplateColumns = `repeat(${size}, 50px)`;
        for (let row = 0; row < size; row++) {
            const rowArray = [];
            for (let col = 0; col < size; col++) {
                const cell = document.createElement('div');
                cell.classList.add('cell');
                cell.dataset.row = row;
                cell.dataset.col = col;
                cell.dataset.revealed = 'false';
                cell.dataset.flagged = 'false';
                cell.dataset.isBomb = 'false';
                cell.style.backgroundImage = cellImage;
                gameBoard.appendChild(cell);
                rowArray.push(cell);
            }
            board.push(rowArray);
        }
        placeBombs(board, size, bombCount);
        return board;
    }

    function placeBombs(board, size, bombCount) {
        let bombsPlaced = 0;
        while (bombsPlaced < bombCount) {
            let row = Math.floor(Math.random() * size);
            let col = Math.floor(Math.random() * size);
            let cell = board[row][col];
            if (cell.dataset.isBomb === 'false') {
                cell.dataset.isBomb = 'true';
                bombsPlaced++;
            }
        }
    }

    function addClickHandlers() {
        document.querySelectorAll('.cell').forEach(cell => {
            cell.addEventListener('click', function() {
                if (!gameActive) return;
                if (flagMode) {
                    flagCell(this);
                } else {
                    if (this.dataset.revealed === 'true' || this.dataset.flagged === 'true') return;
                    if (this.dataset.isBomb === 'true') {
                        revealBomb(this);
                    } else {
                        const number = recClear(board, parseInt(this.dataset.row), parseInt(this.dataset.col));
                        this.style.backgroundImage = number > 0 ? numberImages[number] : emptyImage;
                    }
                }
            });

            cell.addEventListener('contextmenu', function(event) {
                event.preventDefault();
                flagCell(this);
            });
        });
    }

    document.getElementById('toggleFlagButton').addEventListener('click', function() {
        flagMode = !flagMode;
        this.textContent = `Flag Mode: ${flagMode ? 'ON' : 'OFF'}`;
    });

    function recClear(board, row, col) {
        if (row < 0 || row >= boardSize || col < 0 || col >= boardSize) {
            return 0;
        }
        const cell = board[row][col];
        if (cell.dataset.revealed === 'true' || cell.dataset.isBomb === 'true') {
            return 0;
        }
        cell.dataset.revealed = 'true';
        let count = 0;
        for (let dRow = -1; dRow <= 1; dRow++) {
            for (let dCol = -1; dCol <= 1; dCol++) {
                if (dRow === 0 && dCol === 0) continue; // Skip the cell itself
                if (isBomb(board, row + dRow, col + dCol)) {
                    count++;
                }
            }
        }
        if (count === 0) {
            // Clear surrounding cells if this is a zero cell
            for (let dRow = -1; dRow <= 1; dRow++) {
                for (let dCol = -1; dCol <= 1; dCol++) {
                    recClear(board, row + dRow, col + dCol);
                }
            }
        }
        cell.style.backgroundImage = numberImages[count] || emptyImage;
        return count;
    }

    function isBomb(board, row, col) {
        if (row < 0 || row >= boardSize || col < 0 || col >= boardSize) {
            return false;
        }
        return board[row][col].dataset.isBomb === 'true';
    }

    function updateBombsLeftDisplay() {
        const bombsLeft = bombCount - flagsCount;
        document.getElementById('bombsLeftDisplay').textContent = `Bombs Left: ${bombsLeft}`;
    }



    function flagCell(cell) {
        if (!gameActive || cell.dataset.revealed === 'true') {
            return;
        }
        const wasFlagged = cell.dataset.flagged === 'true';
        if (!wasFlagged && flagsCount >= bombCount) {
            return; // Don't allow more flags than bombs
        }
        cell.dataset.flagged = wasFlagged ? 'false' : 'true';
        cell.style.backgroundImage = wasFlagged ? cellImage : flagImage;
        flagsCount += wasFlagged ? -1 : 1;
        updateBombsLeftDisplay();
        checkWinCondition();
    }

    function checkWinCondition() {
        if (flagsCount === bombCount && allBombsFlagged()) {
            gameActive = false;
            const gameBoard = document.getElementById('gameBoard');
            gameBoard.style.backgroundImage = victoryImage;
            gameBoard.style.backgroundSize = "cover";
            gameBoard.style.backgroundPosition = "center";
            gameBoard.style.backgroundRepeat = "no-repeat";
            alert('Congratulations, you win!');
        }
    }

    function allBombsFlagged() {
        const cells = Array.from(document.querySelectorAll('.cell')); // Convert NodeList to Array
        const bombCells = cells.filter(cell => cell.dataset.isBomb === 'true');
        const flaggedCells = cells.filter(cell => cell.dataset.flagged === 'true');
    
        console.log(`Bomb Cells: ${bombCells.length}, Flagged Cells: ${flaggedCells.length}`);
    
        if (flaggedCells.length !== bombCells.length) {
            return false;
        }
    
        return flaggedCells.every(cell => cell.dataset.isBomb === 'true');
    }
    

    function revealBomb(cell) {
        gameActive = false;
        cell.style.backgroundImage = bombImage;
        cell.classList.add('bomb');
        alert('Game Over! You hit a bomb.');
        document.querySelectorAll('.cell').forEach(c => {
            if (c.dataset.isBomb === 'true' && c.dataset.flagged === 'false') {
                c.style.backgroundImage = bombImage;
            } else if (c.dataset.isBomb === 'false' && c.dataset.flagged === 'true') {
                c.style.backgroundImage = notFlagImage;
            }
        });
    }

    function showVictoryImage() {
        const victoryContainer = document.createElement('div');
        victoryContainer.setAttribute('id', 'victoryContainer');
        const victoryImg = document.createElement('img');
        victoryImg.setAttribute('id', 'victoryImage');
        victoryImg.src = 'victoryImage.png'; // Path to your victory image
        victoryContainer.appendChild(victoryImg);
        document.getElementById('gameBoard').appendChild(victoryContainer);
    }
    
    function clearVictoryImage() {
        const victoryContainer = document.getElementById('victoryContainer');
        if (victoryContainer) {
            victoryContainer.remove();
        }
    }
    
    // Modify the checkWinCondition function to call showVictoryImage when the win condition is met
    function checkWinCondition() {
        console.log(`Checking win condition: flagsCount = ${flagsCount}, bombCount = ${bombCount}`);
        if (flagsCount === bombCount && allBombsFlagged()) {
            console.log('Win condition met. Showing victory image.');
            gameActive = false;
            showVictoryImage();
            alert('Congratulations, you win!');
        } else {
            console.log('Win condition not met.');
        }
    }
    
  document.getElementById('resetButton').addEventListener('click', function() {
        clearVictoryImage();
        initializeGame();
    });

    document.getElementById('boardSizeSelect').addEventListener('change', initializeGame);

    initializeGame();
});
