function gauss(ta, tb, tx, ts){
            var permutations = 0;
            var det;
            for (var i = 0; i < ts - 1; i++)
            {
                // меняем текущую строку с той, у которой диагональный
                // элемент ненулевой и наибольший
                var imax = i;
                for (var j = i; j < ts; j++)
                {
                    if ((ta[j][i] > ta[imax][i]) && (ta[j][i] != 0))
                        imax = j;
                }
                if (imax != i)
                {
                    var tmp;
                    for (var t = 0; t < ts; t++)
                    {
                        tmp = ta[imax][t];
                        ta[imax][t] = ta[i][t];
                        ta[i][t] = tmp;
                    }
                    tmp = tb[imax];
                    tb[imax] = tb[i];
                    tb[i] = tmp;

                    permutations++;
                }

                // теперь прямой ход по данной строке
                for (var k = i + 1; k < ts; k++)
                {
                    if (ta[i][i] == 0)
                        return false;
                    var divider = ta[k][i] / ta[i][i];
                    for (var l = i; l < ts; l++)
                    {
                        ta[k][l] = ta[k][l] - ta[i][l] * divider;
                    }
                    tb[k] = tb[k] - tb[i] * divider;
                }
            }

            var mult = (permutations % 2 == 0 ? 1 : -1);
            for (var i = 0; i < ts; i++)
                mult *= ta[i][i];
            det = mult;

            // все, прямой ход сделан, теперь идем обратно
            for (var i = ts - 1; i >= 0; i--)
            {
                for (var j = i + 1; j < ts; j++)
                    tb[i] -= tx[j] * ta[i][j];
                if (ta[i][i] == 0)
                    return false;
                tx[i] = tb[i] / ta[i][i];
            }   
            return 1;
}

function sortrows(Matrix, RightPart, Count, index) {
    var MaxElement = Matrix[index][index];
    var MaxElementIndex = index;
    for (var i = index + 1; i < Count; i++)
    {
        if (Matrix[i][index] > MaxElement)
        {
            MaxElement = Matrix[i][index];
            MaxElementIndex = i;
        }
    }
 
      //теперь найден максимальный элемент ставим его на верхнее место
    if (MaxElementIndex > index)//если это не первый элемент
    {
        var Temp;
 
        Temp = RightPart[MaxElementIndex];
        RightPart[MaxElementIndex] = RightPart[index];
        RightPart[index] = Temp;
 
        for (var i = 0; i < Count; i++)
        {
            Temp = Matrix[MaxElementIndex][i];
            Matrix[MaxElementIndex][i] = Matrix[index][i];
            Matrix[index][i] = Temp;
        }
    }    
}

function gauss2(Matrix, RightPart, Answer, Count) {

      for (var i = 0; i < Count - 1; i++)
      {
        sortrows(Matrix, RightPart, Count, i);
        for (var j = i + 1; j < Count; j++)
        {
          if (Matrix[i][i] != 0) //если главный элемент не 0, то производим вычисления
          {
            var MultElement = Matrix[j][i] / Matrix[i][i];
            for (var k = i; k < Count; k++)
              Matrix[j][k] -= Matrix[i][k] * MultElement;
            RightPart[j] -= RightPart[i] * MultElement;
          }
          //для нулевого главного элемента просто пропускаем данный шаг
        }
      }
 
      //ищем решение
      for (var i = Count - 1; i >= 0; i--)
      {
        Answer[i] = RightPart[i];
 
        for (var j = Count - 1; j > i; j--)
          Answer[i] -= Matrix[i][j] * Answer[j];
 
        Answer[i] /= Matrix[i][i];
 
      }
      return 0;
    
}