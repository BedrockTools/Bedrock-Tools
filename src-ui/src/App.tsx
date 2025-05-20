import React from "react";
import ReactDOM from "react-dom/client";
import "./App.css";
import Main from "./Main";

ReactDOM.createRoot(
    document.getElementById("root") as HTMLElement
).render(
    <React.StrictMode>
        <div className="background" />
        <Main />
    </React.StrictMode>
);