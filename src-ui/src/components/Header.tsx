import React from "react";
const Space = ({ children }: { children: React.ReactNode }) => {
    return (
        <React.StrictMode>
            <div
                style={{
                    alignItems: "center",
                    display: "flex",
                    flexDirection: "row",
                    position: "absolute",
                    right: 0,
                    // @ts-ignore
                    "-webkit-app-region": "no-drag",
                }}
            >{children}</div>
        </React.StrictMode>
    )
};

import { Property } from "csstype";

type HeaderButtonProps = {
    src: string;
    width?: Property.Width;
    height?: Property.Width;
};
const HeaderButton = ({ src, width = "10px", height = "10px" }: HeaderButtonProps) => {
    return (
        <React.StrictMode>
            <div className="headerButton" style={{ marginRight: 0, marginLeft: 0 }}>
                <img src={src} style={{ imageRendering: "pixelated", width, height, }} />
            </div>
        </React.StrictMode>
    )
};

import arrowBack from "../../assets/ui/arrow_back.png";
import settings from "../../assets/ui/settings.png";
import close from "../../assets/ui/close.png";
import maximize from "../../assets/ui/maximize.png";
import minimize from "../../assets/ui/minimize.png";
export default ({ backButton = false }) => {
    return (
        <React.StrictMode>
            <div className="header">
                <div className="header_">
                    <div className="header__">
                        <div style={{
                            position: "absolute",
                            left: "0.4rem",
                            // @ts-ignore
                            "-webkit-app-region": "no-drag"
                        }}>
                            {backButton ? (
                                <HeaderButton src={arrowBack} height="16px" width="16px" />
                            ) : null}
                        </div>

                        <div className="headerTitle">
                            <div className="headerTitle_">Meow!</div>
                        </div>

                        <Space>
                            <div style={{ display: "flex", flexDirection: "row", marginLeft: "0.4rem", marginRight: "0.4rem" }}>
                                <HeaderButton src={minimize} />
                                <HeaderButton src={maximize} />
                                <HeaderButton src={close} />
                            </div>
                        </Space>
                    </div>
                    <div className="headerShadow"/>
                </div>
            </div>
        </React.StrictMode>
    );
};