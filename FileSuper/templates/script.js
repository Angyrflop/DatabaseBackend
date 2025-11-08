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