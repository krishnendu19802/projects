let btns = document.querySelectorAll('.btn_tab');
let disp = document.querySelector('.display_board');
let i = 1;
let flag = 0;
let btnlog = [0, 0, 0, 0, 0, 0, 0, 0, 0];
let val = 0;
btns.forEach(button => button.addEventListener("click", function (e) {
    if (button.innerHTML !== "X" && button.innerHTML !== "O" && flag != 1) {
        if (i % 2 == 1) {
            button.innerHTML = "X";
            
            val = button.classList[1];

            val = val[3];
            btnlog[val] = 1;
           
            flag = check(btnlog);
            

            if (flag == 1) {
                announce(flag);
                return;
            }
            let text = disp.innerHTML;
            text = text.substring(0, 7) + "2"+text.substring(8,text.length);
            disp.innerHTML = text;
            
        }
        else {
            button.innerHTML = "O";

            val = button.classList[1];

            val = val[3];
            btnlog[val] = 2;
            
            flag = check(btnlog);
            
            if (flag == 1) {
                announce(flag);
                return;
            }
            let text = disp.innerHTML;
            
            text = text.substring(0, 7) + "1"+text.substring(8,text.length);
            disp.innerHTML = text;
           


        }

        

        i++;
        if (i > 9) {
            
            announce(0);
        }
    }


}));
//checking condition for winning
function check(btnlog) {
    let flag = 0;
    if (btnlog[4] != 0) {

        if (btnlog[0] == btnlog[4] && btnlog[4] == btnlog[8]) {
            flag = 1;
            
        }

        else if (btnlog[2] == btnlog[4] && btnlog[4] == btnlog[6]) {
            flag = 1;
            
        }


        else if (btnlog[1] == btnlog[4] && btnlog[4] == btnlog[7]) {
            flag = 1;
            
        }

        else if (btnlog[3] == btnlog[4] && btnlog[4] == btnlog[5]) {
            flag = 1;
            
        }



    }
    if (btnlog[0] != 0) {
        
        if (btnlog[0] == btnlog[3] && btnlog[3] == btnlog[6]) {
            flag = 1;
            
        }

        else if (btnlog[0] == btnlog[1] && btnlog[1] == btnlog[2]) {
            flag = 1;
            
        }


    }
    if (btnlog[8] != 0) {
        if (btnlog[6] == btnlog[7] && btnlog[7] == btnlog[8]) {
            flag = 1;
            
        }

        else if (btnlog[2] == btnlog[5] && btnlog[5] == btnlog[8]) {
            flag = 1;
            
        }

    }
    // console.log(flag);


    return flag;
}

function announce(flag) {
    let ndiv = document.createElement("div");
    let m_area = document.querySelector('.main_area');
    ndiv.classList.add('Announcement');
    if (flag == 1) {
        let text = disp.innerHTML.substring(0,8)+" won";
        disp.remove();
        document.querySelector('.game_area').remove();
        ndiv.innerHTML = text;


    }
    else {
        disp.remove();
        document.querySelector('.game_area').remove();

        ndiv.innerHTML = "MATCH DRAWN";

    }
    let adiv = document.createElement('div');
    let a = document.createElement('a');
    a.href = 'index.html';
    let icon = document.createElement('ion-icon');
    icon.setAttribute('name','reload-circle-outline');
    // icon.classList.add('fas', 'fa-home');

    a.appendChild(icon);
    adiv.append(document.createElement('br'));
    adiv.append(a);
    ndiv.append(adiv);
    m_area.append(ndiv);
}