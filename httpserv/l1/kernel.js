function addData(){
    var num = send();
    var t = [num];
    var x = [num];
    var matrix = [num];

    var table = document.getElementById('tbl');
    var row;
    var col;
    var cod;

    for (var i = 1; i < table.rows.length - 1; i++)
    {        
        matrix[i - 1] = [num];
        t[i - 1] = 1; 
        for (var j = 1; j < num + 1; j++)
        {
            row = table.rows[j];
            col = row.cells[i];
            matrix[i - 1][j - 1] = +col.innerText;
            if (j == i) {
                for (var k = 1;  k < num + 1; k++) {
                    col = table.rows[j];
                    cod = col.cells[k];
                    matrix[i - 1][j - 1] -= +cod.innerText;    
                }                
            }
            matrix[i - 1][j - 1]++;
        }
    }  

    if(gauss(matrix, t, x, num) != 0)
        alert("Error");


    row = table.rows[num + 1];

    for (var j = 1, col; col = row.cells[j]; j++){
        col.innerText = x[j - 1].toString()
    }
}