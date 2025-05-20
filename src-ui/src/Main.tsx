import React from "react";
import Header from "./components/Header";
export default () => {
    return (
        <React.StrictMode>
            <div className="backdrop" />
            <Header backButton={true} />
            
            <div>Meow!</div>
        </React.StrictMode>
    );
};