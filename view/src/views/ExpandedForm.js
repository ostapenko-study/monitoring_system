import React, { useState } from 'react';

import './ExpandedForm.css'

export const ExpandedForm = ({title, children}) => {

    const [isVisible, setIsVisible] = useState(false)

    const buttonHandler = () => {
        setIsVisible(!isVisible)
    }

    return (
        <div>
            <div className="container">
                <div className="title">{title}</div>
                <button className={isVisible ? "visible_btn" : "no_visible_btn"} onClick={buttonHandler} type="button" />
            </div>
            {isVisible ? <div className="child">{children}</div> : null}
        </div>
    )
}

export default ExpandedForm;