var str = prompt('Сколько состояний', 4);
var num = +str;

var table  = document.createElement("table");
table.setAttribute("id", "tbl");
table.setAttribute("border", "1");
table.align = "left";
table.width = 500;


for(var i = 0; i < num + 2; ++i)
{
    var newRow = table.insertRow(i);
    if (i == 0) {
        newRow.className = "special";
    }
    for(var j = 0; j < num + 1; ++j)
    {
        var newCell = newRow.insertCell(j);
        newCell.innerText = "0";
        if ((i == 0) || (j == 0)) {
            newCell.className = "special";
        }
        else{
            newCell.contentEditable = "true"
        }
    }
}

for(var i = 1; i < num + 1 ; ++i)
{
    var rb = table.rows[i];
    rb.cells[0].innerText = "S" +  i.toString();
}

var rb = table.rows[0];
for(var i = 1; i < num + 1; ++i)
{    
    rb.cells[i].innerText = "S" + i.toString();
}

var rb = table.rows[num +1];
rb.cells[0].innerText = "t";

document.body.appendChild(table);

function send(){
    return num;
}