
function clearfunc() {
    let x = document.getElementById('displayarea');
    x.innerHTML = "";
}
function funcnum(a) {
    let x = document.getElementById('displayarea');
    let content = x.innerHTML;
    x.innerHTML = content + a;
}

function funcsymb(a) {
    let x = document.getElementById('displayarea');
    let content = x.innerHTML;
    x.innerHTML = content + a;
}
function errmes(i) {
    let x = document.getElementById('displayarea');
    let content = x.innerHTML;
    if(i!=1)
    x.innerHTML = "Error!";
    else
    x.innerHTML="only Integers accepted!";
}

function dellast()
{
    let x = document.getElementById('displayarea');
    let content = x.innerHTML;
    let updated=content.substring(0,content.length-1);
    x.innerHTML=updated;
}
function equalfunc() {
    let x = document.getElementById('displayarea');
    let content = x.innerHTML;
    let j=0;
    var val1 = 0, val2 = 0, y = '', i, ch = '', out = 0,flag=0;
    for (i = 0; i < content.length; i++) {
        y = content.charAt(i);
        // console.log(y);
        if(y=='.')
        {
            errmes(1);
            return;
        }
        if(y==')')
        // continue;
        {
            if(flag==1)
            continue;
            else
            {
                errmes();
                return;
            }
            
        }
        if(y=='(')
        {
            if(content.charAt(i+1)=='-')
            {
                flag=1;
                i++;
                j++;
                continue;
            }
            else
            {
               continue;
            }
        }
        if (y == '+'||y=='*'||y=='-'||y=='/'||y=='%') {
            ch = y;
            if(i==0)
            {
                errmes();
                return;
            }
            break;
        }
        else
        // {
            // if(flag!=1)
            val1 = val1 * 10 + Number(y);
            
    }
    if(flag==1)
    val1=val1*-1;
    flag=0;
    x.innerHTML = val1;
    for (i = i + 1; i < content.length; i++) {
        y = content[i];
        if(y==')')
        // continue;
        {
            if(flag==1)
            continue;
            else
            {
                errmes();
                return;
            }
        }
        if(y=='(')
        {
            if(content.charAt(i+1)=='-')
            {
                flag=1;
                i++;
                continue;
            }
            else
            {
               continue;
            }
        }
        val2 = val2 * 10 + Number(y);
    }
    if(flag==1)
    val2=val2*-1;
    // console.log(val1);
    // console.log(val2);
    y=content.charAt(content.length-1);
    if(y == '+'||y=='*'||y=='-'||y=='/'||y=='%')
    {
        errmes();
        return;
    }
    
    if (ch == '+')
        out = val1 + val2;
    else if(ch=='*')
    out=val1*val2;
    else if(ch=='/')
    out=val1/val2;
    else if(ch=='-')
    out=val1-val2;
    else if(ch=='%')
    out=val1%val2;
        // console.log(out);
    x.innerHTML=out;


}