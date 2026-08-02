slint::slint! {
    import { Button } from "std-widgets.slint";

    export component MainWindow inherits Window {
        width: 360px;
        height: 640px;
        background: #1e1e2e;

        VerticalBox {
            alignment: center;
            spacing: 20px;

            Text {
                text: "Hello from Rust + Slint!";
                color: #cdd6f4;
                font-size: 24px;
                horizontal-alignment: center;
            }

            Button {
                text: "Click Me!";
                clicked => {
                    self.text = "It Works!";
                }
            }
        }
    }
}

#[no_mangle]
fn android_main(app: slint::android::AndroidApp) {
    slint::android::init(app).unwrap();
    MainWindow::new().unwrap().run().unwrap();
}
