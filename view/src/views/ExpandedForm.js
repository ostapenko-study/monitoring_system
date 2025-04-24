import React, { useState } from 'react';

import './ExpandedForm.css'

export const ExpandedForm = ({title, children}) => {

    const [isVisible, setIsVisible] = useState(false)

    const buttonHandler = () => {
        setIsVisible(!isVisible)
    }

    return (
        <div>
            <div class="container">
                <div class="title">{title}</div>
                <button class={isVisible ? "visible_btn" : "no_visible_btn"} onClick={buttonHandler} type="button" />
            </div>
            {isVisible ? <div class="child">{children}</div> : null}
        </div>
    )
}

export default ExpandedForm;