function register() {
    const username = document.getElementById("username").value;
    const password = document.getElementById("password").value;

    console.log("Attempting to register:", username);

    fetch("/register", {
        method: "POST",
        headers: { "Content-Type": "application/json" },
        body: JSON.stringify({ username, password })
    })
    .then(res => {
        console.log("Response status:", res.status);
        return res.text();
    })
    .then(data => {
        console.log("Response data:", data);
        alert(data);
    })
    .catch(error => {
        console.error("Fetch error:", error);
        alert("Error: " + error);
    });
}

function login() {
    const username = document.getElementById("username").value;
    const password = document.getElementById("password").value;

    console.log("Attempting to login:", username);

    fetch("/login", {
        method: "POST",
        headers: { "Content-Type": "application/json" },
        body: JSON.stringify({ username, password })
    })
    .then(res => {
        console.log("Response status:", res.status);
        return res.text();
    })
    .then(data => {
        console.log("Response data:", data);
        alert(data);
        
    })
    .catch(error => {
        console.error("Fetch error:", error);
        alert("Error: " + error);
    });
}
//Created by Claude ai. Other function were found on stack overflow and github. Why? Because i cant code in js. sorry.
function deleteAccount() {
    const username = document.getElementById("username").value;
    const password = document.getElementById("password").value;

    console.log("Attempting to delete account:", username);

    if (!confirm("Are you sure you want to delete your account? This action cannot be undone.")) {
        console.log("Account deletion cancelled by user");
        return;
    }

    fetch("/delete", {
        method: "DELETE",
        headers: { "Content-Type": "application/json" },
        body: JSON.stringify({ username, password })
    })
    .then(res => {
        console.log("Response status:", res.status);
        const status = res.status;
        return res.text().then(data => ({ status, data }));
    })
    .then(({ status, data }) => {
        console.log("Response data:", data);
        alert(data);
        
        
        if (status === 200 || data.includes("deleted") || data.includes("successful")) {
            window.location.href = "/register";
        }
    })
    .catch(error => {
        console.error("Fetch error:", error);
        alert("Error: " + error);
    });
}