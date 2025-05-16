import { defineConfig } from "@rsbuild/core";
import { pluginReact } from "@rsbuild/plugin-react";

export default defineConfig({
    source: {
        entry: {
            index: "./src/App.tsx"
        },
    },
    html: {
        title: "Bedrock Tools",
        favicon: "./assets/icon.png",
        appIcon: {
            name: "Bedrock Tools",
            filename: "manifest.json",
            icons: []
        },
        meta: {
            description: "Hello, world!",
        },
    },
    output: {
        legalComments: "linked",
        filename: {
            js: "[name].[contenthash:5].js",
        },
        distPath: {
            root: "dist",
            html: "./",
            assets: "assets",

            js: "assets",
            jsAsync: "assets/async",
            css: "assets",
            cssAsync: "assets/async",
            svg: "assets",
            font: "assets",
            wasm: "assets",
            image: "assets",
            media: "assets",
        },
    },
    plugins: [ pluginReact() ],
});