function funct_class() {
    var elem = document.getElementById("button_class");
    if (elem.value == "Hide Classes")
        elem.value = "Show Classes";
    else
        elem.value = "Hide Classes";
    var e = [];
    var e = document.getElementsByClassName("class_div");
    for (var i=0;i<e.length;++i) {
        if (!e[i]) return true;
        if (e[i].style.display == "none") {
            e[i].style.display = "inline"
        }
        else {
            e[i].style.display = "none"
        }
    } return true;
}
function funct_struct() {
    var elem = document.getElementById("button_struct");
    if (elem.value == "Hide Structures")
        elem.value = "Show Structures";
    else
        elem.value = "Hide Structures";
    var e = [];
    var e = document.getElementsByClassName("struct_div");
    for (i in e) {
        if (!e[i])
            return true;
        if (e[i].style.display == "none") {
            e[i].style.display = "inline"
        }
        else {
            e[i].style.display = "none"
        }
    } return true;
}
function funct_funct() {
    var elem = document.getElementById("button_funct");
    if (elem.value == "Hide Functions")
        elem.value = "Show Functions";
    else elem.value = "Hide Functions";
    var e = [];
    var e = document.getElementsByClassName("function_div");
    for (var i=0;i<e.length;++i) {
        if (!e[i])
            return true;
        if (e[i].style.display == "none") {
            e[i].style.display = "inline"
        }
        else {
            e[i].style.display = "none"
        }
    } return true;
}
function funct_comment() {
    var elem = document.getElementById("button_comment");
    if (elem.value == "hide comments")
        elem.value = "show comments";
    else
        elem.value = "hide comments";
    var e = [];
    var e = document.getElementsByClassName("SLC_Div");
    for (var i =0; i<e.length;++i) {
        if (!e[i])
            break;    
        if (e[i].style.display == "none") {
            e[i].style.display = "inline"
        }
        else {
            e[i].style.display = "none"
        }
    }
    var f = document.getElementsByClassName("MLC_Div");
    for (var i=0;i<f.length;++i) {
        if (!f[i])
            return true;
        if (f[i].style.display == "none") {
            f[i].style.display = "inline"
        }
        else {
            f[i].style.display = "none"
        }
    }
    return true;
}