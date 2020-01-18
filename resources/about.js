let currentMe = true;
const changeName = () => {
    if (currentMe) {
        document.getElementById("icon").src = "kuriboh.png";
    } else {
        document.getElementById("icon").src = "hieupro.jpg";
    }
    currentMe = !currentMe;
};
