
document.addEventListener('click', function (e) {
    let btn = e.target;
    if (btn.classList.contains('add-button')) {
        let text = document.querySelector('.to-add');
        if (text.value === "")
            alert("enter a task");
        else {
            let mainli = document.querySelector('.task-list');

            let tclass = "";
            let lival = document.createElement('li');
            {
                if (text.value.indexOf(" ") != -1)
                    tclass = text.value.substring(0, text.value.indexOf(" "));
                else
                    tclass = text.value;
            }
            lival.classList.add('task-item', tclass);

            let new_task = document.createElement('div');
            new_task.classList.add('item', tclass);
            // new_task.classList.add
            new_task.append(text.value);
            // alert(new_task);
            let rem_btn = document.createElement('button');
            rem_btn.classList.add('btn', 'rem-button', tclass);

            rem_btn.innerHTML = "X"

            new_task.append(rem_btn);
            lival.append(new_task);
            mainli.appendChild(lival);
            text.value = "";
        }
    }
    else if (btn.classList.contains('rem-button')) {
        let tclass = btn.classList[2];
        let titem = document.getElementsByClassName(tclass)[0];
        console.log(titem);
        // sleep(Time in ms).then(() => {
        //     //// code
        //     })
        titem.classList.add('removing');
        // ttask.style.textDecorationStyle="line-through";
        // let mainli = document.querySelector('.task-list');
        setTimeout(() => {
            // element.remove();
            titem.remove();
          }, 2000);

    }
})